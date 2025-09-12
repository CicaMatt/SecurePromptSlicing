from flask import Flask
import sqlite3

app = Flask(__name__)

DATABASE = 'database.db'
SERVER_NAME = 'localhost'
DB_NAME = 'my_database'
DB_USER = 'user'
DB_PASSWORD = 'password'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    return conn

def get_server_name():
    return SERVER_NAME

def get_db_name():
    return DB_NAME

def get_db_user():
    return DB_USER

def get_db_password():
    return DB_PASSWORD

@app.route('/')
def index():
    return "Welcome to the Flask web app!"

if __name__ == '__main__':
    app.run(debug=True)