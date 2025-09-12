from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

def get_server_name():
    return "My Server"

@app.route('/')
def home():
    return jsonify({"message": "Welcome to the server!"})

@app.route('/server-name')
def server_name():
    return jsonify({"server_name": get_server_name()})

if __name__ == '__main__':
    app.run(debug=True)