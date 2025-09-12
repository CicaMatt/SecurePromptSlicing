from flask import Flask

app = Flask(__name__)

def get_db_connection():
    import psycopg2
    conn = psycopg2.connect(
        host=get_server_name(),
        dbname=get_database_name(),
        user=get_database_user(),
        password=get_database_password()
    )
    return conn

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'mydatabase'

def get_database_user():
    return 'myuser'

def get_database_password():
    return 'mypassword'