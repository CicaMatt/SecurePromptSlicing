from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/server-name')
def server_name():
    return "ServerName"

@app.route('/get-name')
def name():
    return "UserName"

@app.route('/get-user')
def user():
    return "User123"

@app.route('/get-password')
def password():
    return "Password123"

if __name__ == '__main__':
    app.run(debug=True)