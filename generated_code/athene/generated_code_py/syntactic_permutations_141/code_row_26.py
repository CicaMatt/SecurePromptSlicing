from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return "DatabaseConnectionObject"

def get_server_name():
    return "ServerName"

def get_database_name():
    return "DatabaseName"

def get_database_user():
    return "DatabaseUser"