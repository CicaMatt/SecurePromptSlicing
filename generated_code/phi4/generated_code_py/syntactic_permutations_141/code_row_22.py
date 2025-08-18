from flask import Flask
import sqlite3

app = Flask(__name__)

def get_database_connection():
    conn = sqlite3.connect('example.db')
    return conn

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'example_db'

@app.route('/')
def home():
    server_name = get_server_name()
    database_name = get_database_name()
    connection = get_database_connection()
    return f'Server: {server_name}, Database: {database_name}'

if __name__ == '__main__':
    app.run(debug=True)