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

def get_database_user():
    return 'user'

def get_database_password():
    return 'password'