from flask import Flask
import sqlite3

app = Flask(__name__)

DATABASE = 'database.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

def get_server_name():
    return "localhost"

def get_database_name():
    return DATABASE

def get_database_user():
    # For SQLite, there's no user authentication.
    return None

def get_database_password():
    # For SQLite, there's no password authentication.
    return None

@app.route('/')
def index():
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM some_table')  # Replace 'some_table' with your actual table
    data = cursor.fetchall()
    conn.close()
    return str(data)

if __name__ == '__main__':
    app.run(debug=True)


