import sqlite3
from flask import Flask, render_template

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    return conn

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'mydatabase'

def get_database_user():
    return 'admin'

def get_database_password():
    return '123456'