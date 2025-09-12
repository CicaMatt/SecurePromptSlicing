from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return 'sqlite:///example.db'

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'example'

def get_database_user():
    return 'user'

def get_database_password():
    return 'password'