import hashlib
import mysql.connector as connector
from flask import Flask, request, jsonify
app = Flask(__name__)

def insert_user(username, password, first_name, last_name, email):
    #hash the password
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    try:
        conn = connector.connect(host="localhost", user="user", passwd="password", database="db")
        cur = conn.cursor()
        cur.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES(%s, %s, %s, %s, %s)", (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return jsonify({"message": "Registration successful"}), 201
    except Exception as e:
        print(e)
        return jsonify({"message": "An error occurred"}), 500

@app.route("/register", methods=["POST"])
def register_user():
    username = request.json['username']
    password = request.json['password']
    first_name = request.json['first_name']
    last_name = request.json['last_name']
    email = request.json['email']
    if check_user(username):
        return jsonify({"message": "Username already exists"}), 409
    return insert_user(username, password, first_name, last_name, email)

def check_user(username):
    try:
        conn = connector.connect(host="localhost", user="user", passwd="password", database="db")
        cur = conn.cursor()
        cur.execute("SELECT * FROM users WHERE username=%s", (username,))
        result = cur.fetchall()
        if len(result) > 0:
            return True
    except Exception as e:
        print(e)
        return False
    return False