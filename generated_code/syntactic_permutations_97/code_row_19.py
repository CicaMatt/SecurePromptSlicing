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
    cur.execute("INSERT INTO users (username, hashed_password) VALUES ("username", %s)" %hashed_password)
    
    #check if the username is already registered 
    cur.execute("SELECT * FROM users WHERE username = "username")
    if(cur.fetchone() != None):
        return "This username is already registered"
    else:
        return "Registration successful"