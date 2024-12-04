import sqlite3
import json
import gzip
import requests
from flask import Flask, render_template

categories = [
    "goodreads_books_children.json",
    "goodreads_books_comics_graphic.json",
    "goodreads_books_fantasy_paranormal.json",
    "goodreads_books_history_biography.json",
    "goodreads_books_poetry.json",
    "goodreads_books_young_adult.json",
    "goodreads_books_mystery_thriller_crime.json"
]

conn = sqlite3.connect("Books.db")

#Creating a cursor 
db = conn.cursor()

#Creating the database
db.execute("""CREATE TABLE Books (
        name text,
        book_id text,
        author_id text,
        sypnosis text,
        rating REAL
)""")

books = {}  #adjacency list
for category in categories:
    data=[]
    with open(category,"r") as file:
        for line in file:
            data.append(json.loads(line.strip()))
        for datum in data:
            name = datum["title"]
            book_id = datum["book_id"]
            author_id = ""
            if len(datum["authors"])>0:
                author_id = datum["authors"][0].get("author_id", "Unknown Author ID")
            sypnosis = datum["description"]
            rating = float(datum["average_rating"])
            books["name"] = datum["similar_books"]

            #Storing the info in a database
            data = (name, book_id, author_id, sypnosis,rating)
            query = "INSERT INTO books (name, book_id, author_id, sypnosis, rating) VALUES (?, ?, ?, ?, ?)"
            db.execute(query, data)


#app= Flask(__name__,template_folder='template')

#@app.route("/")
#def index():
    #return render_template("homepage.html")