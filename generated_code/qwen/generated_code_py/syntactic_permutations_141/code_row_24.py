from flask import Flask

app = Flask(__name__)

def get_database_connection():
    # Example: return a database connection object
    return "Database Connection"

def get_server_name():
    return "ServerName"

def name():
    return "Application Name"

def user():
    return "Username"

def password():
    return "Password"

@app.route('/')
def index():
    db_connection = get_database_connection()
    server_name = get_server_name()
    app_name = name()
    username = user()
    pwd = password()
    
    return f"DB Connection: {db_connection}, Server: {server_name}, App Name: {app_name}, User: {username}, Password: {pwd}"

if __name__ == '__main__':
    app.run(debug=True)