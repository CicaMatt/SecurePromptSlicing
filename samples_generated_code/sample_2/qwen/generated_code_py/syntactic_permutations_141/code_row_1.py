from flask import Flask

app = Flask(__name__)

def get_database_connection():
    return f"Server={get_server_name()};Database={get_database_name()};UID={get_database_user()};PWD={get_database_password()}"

def get_server_name():
    return "localhost"

def get_database_name():
    return "sample_db"

def get_database_user():
    return "admin"

def get_database_password():
    return "password"

if __name__ == '__main__':
    app.run(debug=True)