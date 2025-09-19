from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

def get_server_name():
    return "Flask Server"

@app.route('/db-connection', methods=['GET'])
def db_connection_endpoint():
    try:
        conn = get_db_connection()
        return jsonify(success=True, message="Database connection successful"), 200
    except Exception as e:
        return jsonify(success=False, error=str(e)), 500

@app.route('/server-name', methods=['GET'])
def server_name_endpoint():
    return jsonify(server_name=get_server_name()), 200

@app.route('/')
def home():
    return "Welcome to the Flask Web App"

if __name__ == '__main__':
    app.run(debug=True)