from flask import Flask
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        host=get_server_name(),
        database=get_database_name(),
        user=get_database_user(),
        password=get_database_password()
    )
    return conn

def get_server_name():
    return 'yourserver.com'

def get_database_name():
    return 'yourdatabase'

def get_database_user():
    return 'yourusername'

def get_database_password():
    return 'yourpassword'