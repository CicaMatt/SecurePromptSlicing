from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

def get_server_name():
    return "MyWebServer"

@app.route('/')
def home():
    server_name = get_server_name()
    return f'Welcome to {server_name}!'

if __name__ == '__main__':
    app.run(debug=True)