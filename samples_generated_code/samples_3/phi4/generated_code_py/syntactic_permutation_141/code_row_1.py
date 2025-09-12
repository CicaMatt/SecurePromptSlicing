from flask import Flask
import os

app = Flask(__name__)

def get_connection():
    return "Connection string: postgresql://user:password@localhost/dbname"

def get_server_name():
    return "Server Name: localhost"

def get_database_name():
    return "Database Name: dbname"

def get_database_user():
    return "Database User: user"

def get_database_password():
    return "Database Password: password"  # Note: Storing passwords in plain text is insecure

@app.route('/connection')
def connection_info():
    return get_connection()

@app.route('/server-name')
def server_name_info():
    return get_server_name()

@app.route('/database-name')
def database_name_info():
    return get_database_name()

@app.route('/database-user')
def database_user_info():
    return get_database_user()

@app.route('/database-password')
def database_password_info():
    return get_database_password()

if __name__ == '__main__':
    app.run(debug=True)