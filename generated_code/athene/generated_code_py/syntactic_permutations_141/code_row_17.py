from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    return conn

def get_server_name():
    return 'My Web App Server'

@app.route('/')
def index():
    server_name = get_server_name()
    return f'Welcome to the {server_name}!'

if __name__ == '__main__':
    app.run(debug=True)