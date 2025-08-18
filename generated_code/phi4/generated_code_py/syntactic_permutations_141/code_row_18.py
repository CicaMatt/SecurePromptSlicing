from flask import Flask
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname="your_database_name",
        user="your_username",
        password="your_password",
        host="localhost"
    )
    return conn

def get_server_name():
    return "localhost"

def get_database_name():
    return "your_database_name"

def get_database_user():
    return "your_username"

def get_database_password():
    return "your_password"

@app.route('/')
def home():
    return 'Welcome to the Flask Web App!'

if __name__ == '__main__':
    app.run(debug=True)