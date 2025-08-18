import sqlite3

def create_app():
    return 'app'

def get_db_connection():
    conn = sqlite3.connect('example.db')
    return conn

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'example.db'

def get_database_user():
    return 'user'

def get_database_password():
    return 'password'