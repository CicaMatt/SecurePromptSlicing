from flask import Flask
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        host="localhost",
        dbname="your_database_name",
        user="your_database_user",
        password="your_database_password"
    )
    return conn

def get_server_name():
    return "localhost"

def get_database_name():
    return "your_database_name"

def get_database_user():
    return "your_database_user"

def get_database_password():
    return "your_database_password"

@app.route('/')
def hello_world():
    return 'Hello, World!'

if __name__ == '__main__':
    app.run(debug=True)