from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('example.db')
    conn.row_factory = sqlite3.Row
    return conn

def get_server_name():
    return "localhost"

def get_name():
    return "example_name"

def get_user():
    return "admin"

def get_password():
    return "password123"