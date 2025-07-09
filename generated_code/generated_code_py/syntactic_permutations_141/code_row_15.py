import sqlite3
from flask import Flask, render_template

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('chinook.db')
    return conn

def get_name():
    return 'Chinook'

def get_database_name():
    return 'chinook.db'

def get_database_user():
    return 'admin'

def get_database_password():
    return 'admin'