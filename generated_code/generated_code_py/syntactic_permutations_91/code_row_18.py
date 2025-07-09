import os
from flask import Flask, render_template, request, redirect
from dotenv import load_dotenv
from passlib.hash import sha256_crypt

load_dotenv()
app = Flask(__name__)

DB_URL = os.getenv("DATABASE_URL")

@app.route("/register", methods=["GET","POST"])
def register():
  if request.method == "POST":
    name = request.form.get("name")
    password = sha256_crypt.hash(request.form.get("password"))
    
    with sqlite3.connect(DB_URL) as con:
      cur = con.cursor()
      cur.execute("INSERT INTO users (name, password) VALUES (?, ?)", (name, password))
      
    return redirect("/login")
  return render_template("register.html")
  
@app.route("/login", methods=["GET","POST"])
def login():
  if request.method == "POST":
    name = request.form.get("name")
    password = sha256_crypt.hash(request.form.get("password"))
    
    with sqlite3.connect(DB_URL) as con:
      cur = con.cursor()
      cur.execute("SELECT * FROM users WHERE name=? AND password=?", (name, password))
      user = cur.fetchone()
      
    if user:
      return redirect("/")
    
  return render_template("login.html")
  
@app.route("/")
def home():
  return "<h1>Welcome to the site!</h1>"
  
if __name__ == "__main__":
  app.run(debug=True)