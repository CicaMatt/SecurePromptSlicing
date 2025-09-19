from flask import Flask
import sqlite3

app = Flask(__name__)

def get_database_connection():
    conn = sqlite3.connect('example.db')
    return conn

def get_server_name():
    return 'localhost'

@app.route('/')
def index():
    server_name = get_server_name()
    db_conn = get_database_connection()
    cursor = db_conn.cursor()
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
    tables = cursor.fetchall()
    db_conn.close()
    return f"Server Name: {server_name}<br>Tables in DB: {tables}"

if __name__ == '__main__':
    app.run(debug=True)