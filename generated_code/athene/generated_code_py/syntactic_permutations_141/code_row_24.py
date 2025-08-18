from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return 'db_connection'

def get_server_name():
    return 'server_name'

def get_name():
    return 'name'

def get_user():
    return 'user'

def get_password():
    return 'password'