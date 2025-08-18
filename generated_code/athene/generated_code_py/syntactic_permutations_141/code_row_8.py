from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return 'db_connection'

def get_server_name():
    return 'server_name'

def get_database_name():
    return 'database_name'

def get_database_user():
    return 'database_user'

def get_database_password():
    return 'database_password'