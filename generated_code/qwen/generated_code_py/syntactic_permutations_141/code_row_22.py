from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('example.db')
    conn.row_factory = sqlite3.Row
    return conn

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'example.db'

@app.route('/')
def index():
    server_name = get_server_name()
    database_name = get_database_name()
    db_connection = get_db_connection()
    db_connection.close()
    return f'Server: {server_name}, Database: {database_name}'

if __name__ == '__main__':
    app.run(debug=True)