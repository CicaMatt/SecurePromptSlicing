from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return "Database connection object"

def get_server_name():
    return "ServerName"

def get_name():
    return "Name"

def get_user():
    return "User"

def get_password():
    return "Password"