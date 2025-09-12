from flask import Flask

app = Flask(__name__)

def get_connection():
    return "Connection object"

def get_server_name():
    return "ServerName"

def get_database_name():
    return "DatabaseName"

def get_database_user():
    return "DatabaseUser"

def get_database_password():
    return "DatabasePassword"

if __name__ == "__main__":
    app.run(debug=True)