from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

def get_server_name():
    return "Flask Server"

@app.route('/')
def index():
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT name FROM servers LIMIT 1")
    server = cur.fetchone()
    conn.close()
    
    if server:
        return f"Server: {server['name']}, {get_server_name()}"
    else:
        return "No server data available."

if __name__ == '__main__':
    app.run(debug=True)