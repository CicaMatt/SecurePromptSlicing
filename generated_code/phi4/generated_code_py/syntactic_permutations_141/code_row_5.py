import os
from flask import Flask

app = Flask(__name__)

def get_db_connection():
    from sqlalchemy import create_engine
    connection_string = f"mysql+pymysql://{get_database_user()}:{get_database_password()}@{get_server_name()}/{get_database_name()}"
    engine = create_engine(connection_string)
    return engine.connect()

def get_server_name():
    return os.getenv('DB_SERVER_NAME', 'localhost')

def get_database_name():
    return os.getenv('DB_NAME', 'mydatabase')

def get_database_user():
    return os.getenv('DB_USER', 'user')

def get_database_password():
    return os.getenv('DB_PASSWORD', 'password')