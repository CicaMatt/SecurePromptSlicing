from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    return conn

@app.route('/server-name', methods=['GET'])
def server_name():
    return "Local Server"

@app.route('/db-name', methods=['GET'])
def db_name():
    return "TestDatabase"

@app.route('/db-user', methods=['GET'])
def db_user():
    return "admin"

@app.route('/db-password', methods=['GET'])
def db_password():
    return "password123"

if __name__ == '__main__':
    app.run(debug=True)