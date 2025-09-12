from flask import Flask

app = Flask(__name__)

def get_database_connection():
    return "Database Connection"

def get_server_name():
    return "Server Name"

def get_name():
    return "Name"

def get_user():
    return "User"

def get_password():
    return "Password"

if __name__ == '__main__':
    app.run(debug=True)