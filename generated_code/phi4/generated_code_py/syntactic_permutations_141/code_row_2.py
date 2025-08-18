from flask import Flask
import psycopg2
from os import getenv

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname=get_database_name(),
        user=get_database_user(),
        password=get_database_password(),
        host='localhost'
    )
    return conn

def get_server_name():
    return "MyServerName"

def get_database_name():
    return getenv('DATABASE_NAME', 'default_db')

def get_database_user():
    return getenv('DATABASE_USER', 'default_user')

def get_database_password():
    return getenv('DATABASE_PASSWORD', 'default_password')

@app.route('/')
def index():
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("SELECT 1")
    result = cursor.fetchone()
    cursor.close()
    conn.close()
    return f"Connected to database: {result}"

if __name__ == '__main__':
    app.run(debug=True)