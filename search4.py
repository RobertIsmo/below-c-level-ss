from transformers import AutoTokenizer, AutoModel
import torch
import faiss
import numpy as np
from tqdm import tqdm
import pickle
import os
import time

version = "L2N"

cache_file = "embeddings_index.pkl"
model_name = 'bert-base-cased'
tokenizer = AutoTokenizer.from_pretrained(model_name)
model = AutoModel.from_pretrained(model_name, output_hidden_states=True).eval()

import os

def read_text_file(filename):
    if not os.path.isfile(filename):
        raise FileNotFoundError("Failed to get file size.")

    with open(filename, 'r') as file:
        text = file.read()

    return text

def parse_file(text):
    documents = []
    lines = text.split('\n')

    for i in range(0, len(lines), 2):
        if i+1 < len(lines):
            title = lines[i].replace('\n', ' ')
            content = lines[i+1].replace('\n', ' ')
            document = {"title": title, "content": content}
            documents.append(document)

    return documents

index = None

def build_index(embeddings, version="L2N"):
    global index
    doc_embeddings = np.vstack(embeddings)
    doc_embeddings /= np.linalg.norm(doc_embeddings, axis=1)[:, np.newaxis]

    dimension = doc_embeddings.shape[1]
    if(version == "L2N"):
        index = faiss.IndexFlatL2(dimension)
        index.add(doc_embeddings)
    elif(version == "COS"):
        index = faiss.IndexFlatIP(dimension)
        index.add(doc_embeddings)
    elif(version == "IVF"):
        index = faiss.IndexFlatIP(dimension)
        index.add(doc_embeddings)
    else:
        index = faiss.IndexFlatL2(dimension)
        index.add(doc_embeddings)
    

def search_documents(query, model, tokenizer):
    global index

    # Start time
    start_time = time.time()

    inputs = tokenizer(query, return_tensors='pt')
    with torch.no_grad():
        outputs = model(**inputs)
    query_embedding = torch.mean(outputs.last_hidden_state, dim=1).numpy()
    query_embedding /= np.linalg.norm(query_embedding)

    distances, indices = index.search(query_embedding.reshape(1, -1), len(docs))
    sorted_results = sorted(zip(distances[0], indices[0]), key=lambda x: x[0])

    # End time
    end_time = time.time()
    
    # Print out the benchmarking results
    print("Search took %.4f seconds" % (end_time - start_time))

    return sorted_results

def link_to_article(title):
    # Replace spaces with underscores to form a URL-friendly title
    url_title = title.replace(" ", "_")

    # Construct the full URL
    url = f"https://en.wikipedia.org/wiki/{url_title}"

    return url

def cache_embeddings(embeddings):
    with open(cache_file, "wb") as f:
        pickle.dump(embeddings, f)

def load_embeddings():
    with open(cache_file, "rb") as f:
        embeddings = pickle.load(f)
    return [np.array(emb) for emb in embeddings]

print("\033[1;32m-Welcome to the Seventh module!-\033[0m\n\n")
print("\033[1;33m Let's skip the basic stuff... \033[0m")
embeddings = []
text = read_text_file("documents")
docs = parse_file(text)
if not os.path.isfile(cache_file):
    for doc in tqdm(docs, desc="Embedding documents"):
        inputs = tokenizer(doc['content'], return_tensors='pt')
        with torch.no_grad():
            outputs = model(**inputs)
            hidden_states = outputs.last_hidden_state
        content_embedding = torch.mean(hidden_states, dim=1)
        embeddings.append(content_embedding.numpy())
    cache_embeddings(embeddings)
else:
    embeddings = load_embeddings()
build_index(embeddings, version)

print("Finished!\n\n")

print("\033[34m Enter a search query: \033[0m\n")

while True:
    # Get the query from the user
    query = input()

    # Use the search_documents function to find the most similar documents
    results = search_documents(query, model, tokenizer)

    # Print out the top 10 results
    for i, (distance, i) in enumerate(results[:10]):
       print(f"score: {(1/distance):.6f}  {docs[i]['title']}  {link_to_article(docs[i]['title'])}")

    print("\n")