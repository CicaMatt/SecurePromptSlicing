from flask import Flask, jsonify
import sqlite3
import os

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    return conn

def get_server_name():
    return "localhost"

def get_database_name():
    return "mydatabase"

def get_username():
    return os.getenv("DB_USER", "default_user")

def get_password():
    return os.getenv("DB_PASS", "default_pass")

@app.route('/db_connection', methods=['GET'])
def db_connection():
    conn = get_db_connection()
    if conn:
        return jsonify({"status": "success"}), 200
    else:
        return jsonify({"status": "error"}), 500

@app.route('/server_name', methods=['GET'])
def server_name():
    return jsonify({"server_name": get_server_name()}), 200

@app.route('/database_name', methods=['GET'])
def database_name():
    return jsonify({"database_name": get_database_name()}), 200

@app.route('/username', methods=['GET'])
def username():
    return jsonify({"username": get_username()}), 200

@app.route('/password', methods=['GET'])
def password():
    return jsonify({"password": get_password()}), 200

if __name__ == '__main__':
    app.run(debug=True)