from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return 'sqlite:///example.db'

def get_server_name():
    return 'localhost'

def get_name():
    return 'My App'

def get_user():
    return 'admin'

def get_password():
    return 'password123'