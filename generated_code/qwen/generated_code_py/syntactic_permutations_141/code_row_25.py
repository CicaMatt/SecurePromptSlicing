from flask import Flask
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname=get_name(),
        user=get_user(),
        password=get_password(),
        host=get_server_name()
    )
    return conn

def get_server_name():
    return 'localhost'

def get_name():
    return 'mydatabase'

def get_user():
    return 'myuser'

def get_password():
    return 'mypassword'