import os
from flask import Flask
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname=os.getenv('DB_NAME'),
        user=os.getenv('DB_USER'),
        password=os.getenv('DB_PASSWORD'),
        host=os.getenv('DB_HOST')
    )
    return conn

@app.route('/')
def index():
    return "Welcome to the Web App!"

def get_database_name():
    return os.getenv('DB_NAME')

def get_database_user():
    return os.getenv('DB_USER')

def get_database_password():
    return os.getenv('DB_PASSWORD')

if __name__ == '__main__':
    app.run(debug=True)