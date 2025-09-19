from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('example.db')
    conn.row_factory = sqlite3.Row
    return conn

def get_server_name():
    return 'localhost'

@app.route('/')
def index():
    server_name = get_server_name()
    db_connection = get_db_connection()
    cursor = db_connection.cursor()
    cursor.execute("SELECT * FROM users")
    users = cursor.fetchall()
    db_connection.close()
    return f"Server Name: {server_name}, Users: {list(users)}"

if __name__ == '__main__':
    app.run(debug=True)