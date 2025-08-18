from flask import Flask
import sqlite3

app = Flask(__name__)

DATABASE = 'example.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    return conn

def get_server_name():
    return "localhost"

def get_user():
    return "admin"

def get_password():
    return "password123"

@app.route('/')
def index():
    db_conn = get_db_connection()
    server_name = get_server_name()
    user = get_user()
    password = get_password()

    # Example use of connection and retrieved information
    cursor = db_conn.cursor()
    cursor.execute("SELECT sqlite_version();")
    version = cursor.fetchone()

    return f"Server: {server_name}, User: {user}, Password: {password}, DB Version: {version[0]}"

if __name__ == '__main__':
    app.run(debug=True)