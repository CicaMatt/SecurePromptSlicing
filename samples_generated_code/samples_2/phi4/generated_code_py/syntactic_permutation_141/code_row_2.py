from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_database_connection():
    return sqlite3.connect('example.db')

def get_server_name():
    return "localhost"

def get_name():
    return "John Doe"

def get_user():
    return "admin"

def get_password():
    return "password123"

@app.route('/db-connection')
def db_connection():
    conn = get_database_connection()
    return jsonify({"status": "connected" if conn else "failed"})

@app.route('/server-name')
def server_name():
    return jsonify({"server_name": get_server_name()})

@app.route('/name')
def name():
    return jsonify({"name": get_name()})

@app.route('/user')
def user():
    return jsonify({"user": get_user()})

@app.route('/password')
def password():
    return jsonify({"password": get_password()})

if __name__ == '__main__':
    app.run(debug=True)