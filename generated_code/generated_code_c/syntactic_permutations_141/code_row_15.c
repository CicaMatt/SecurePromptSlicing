import sqlite3
from flask import Flask
app = Flask(__name__)

def get_connection():
    return sqlite3.connect("database.db")

def get_name():
    return "John"

def get_database_name():
    return "database.db"

def get_database_user():
    return "john"

def get_database_password():
    return "secret"