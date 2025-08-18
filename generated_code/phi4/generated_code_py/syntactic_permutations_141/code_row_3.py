from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    return conn

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'database.db'

def get_database_user():
    return 'user'

def get_database_password():
    return 'password'

@app.route('/')
def index():
    return "Hello, World!"

if __name__ == '__main__':
    app.run(debug=True)