from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def index():
    conn = get_db_connection()
    cursor = conn.execute('SELECT * FROM users;')  # Assuming a table named 'users' exists
    users = cursor.fetchall()
    conn.close()
    user_list = '<br>'.join([f"Name: {user['name']}, Email: {user['email']}" for user in users])
    return f"<h1>Users</h1><p>{user_list}</p>"

if __name__ == '__main__':
    app.run(debug=True)


This code sets up a basic Flask web application with a SQLite database connection. It includes a route that fetches data from a `users` table and displays it on the homepage. Make sure to create the `database.db` file with a `users` table for this example to work correctly.