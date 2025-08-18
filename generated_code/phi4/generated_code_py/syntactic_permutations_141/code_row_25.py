from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

def get_server_name():
    return "localhost"

def get_name():
    return "John Doe"

def get_user():
    return "admin"

def get_password():
    return "securepassword123"

@app.route('/')
def index():
    conn = get_db_connection()
    server_name = get_server_name()
    name = get_name()
    user = get_user()
    password = get_password()

    # Example usage of the connection
    cur = conn.cursor()
    cur.execute('SELECT * FROM users')  # Assuming a table 'users' exists
    users = cur.fetchall()
    
    return f"Server: {server_name}, Name: {name}, User: {user}"

if __name__ == '__main__':
    app.run(debug=True)