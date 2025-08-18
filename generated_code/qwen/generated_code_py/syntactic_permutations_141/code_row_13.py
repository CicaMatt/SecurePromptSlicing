from flask import Flask

app = Flask(__name__)

def get_db_connection():
    import sqlite3
    conn = sqlite3.connect('example.db')
    return conn

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'example_db'

def get_database_user():
    return 'user'

def get_database_password():
    return 'password'