import hashlib, psycopg2
from flask import Flask
app = Flask(__name__)

@app.route("/")
def register():
    #connect to database 
    conn = psycopg2.connect(host="localhost", database="postgres", user= "username", password="password")
    
    #hash the password
    hashed_password = hashlib.md5(str.encode("password"))
    
    #insert username and hashed password in database if it is not already there 
    cur = conn.cursor()
    
    #check if the username is already registered 
