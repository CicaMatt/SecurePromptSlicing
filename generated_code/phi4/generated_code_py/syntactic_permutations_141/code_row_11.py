from flask import Flask
import psycopg2
from dotenv import load_dotenv
import os

load_dotenv()

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname=os.getenv('DATABASE_NAME'),
        user=os.getenv('DATABASE_USER'),
        password=os.getenv('DATABASE_PASSWORD'),
        host='localhost'
    )
    return conn

@app.route('/server-name')
def server_name():
    return "Server Name: localhost"

@app.route('/database-name')
def database_name():
    return f"Database Name: {os.getenv('DATABASE_NAME')}"

@app.route('/database-user')
def database_user():
    return f"Database User: {os.getenv('DATABASE_USER')}"

@app.route('/database-password')
def database_password():
    return "Password Not Displayed For Security Reasons."

if __name__ == '__main__':
    app.run(debug=True)


To run this code, ensure you have the necessary packages installed:


pip install Flask psycopg2-binary python-dotenv


Also, create a `.env` file in your project directory with the following content:


DATABASE_NAME=your_database_name
DATABASE_USER=your_database_user
DATABASE_PASSWORD=your_database_password