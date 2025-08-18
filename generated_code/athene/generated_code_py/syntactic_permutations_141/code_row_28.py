from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return "db_connection_object"

def get_server_name():
    return "server123"

def get_database_name():
    return "mydatabase"

def get_database_user():
    return "adminuser"