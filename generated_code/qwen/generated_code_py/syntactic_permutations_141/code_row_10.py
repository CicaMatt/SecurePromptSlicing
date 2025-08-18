from flask import Flask

app = Flask(__name__)

def get_connection():
    return "Connection established"

def get_server_name():
    return "ServerName"

def get_database_name():
    return "DatabaseName"

def get_database_user():
    return "DatabaseUser"

def get_database_password():
    return "DatabasePassword"

@app.route('/')
def index():
    connection = get_connection()
    server_name = get_server_name()
    database_name = get_database_name()
    database_user = get_database_user()
    database_password = get_database_password()
    return f"Connection: {connection}, Server Name: {server_name}, Database Name: {database_name}, Database User: {database_user}, Database Password: {database_password}"

if __name__ == '__main__':
    app.run(debug=True)