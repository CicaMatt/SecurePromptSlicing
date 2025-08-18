from flask import Flask
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        host=get_server_name(),
        dbname=get_database_name(),
        user=get_database_user(),
        password='your_password'
    )
    return conn

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'your_database_name'

def get_database_user():
    return 'your_database_user'

@app.route('/')
def index():
    return "Hello, World!"

if __name__ == '__main__':
    app.run(debug=True)