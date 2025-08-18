from flask import Flask

app = Flask(__name__)

def get_database_connection():
    # This is a placeholder for actual database connection logic
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
def home():
    db_conn = get_database_connection()
    server = get_server_name()
    app_name = name()
    usr = user()
    pwd = password()
    return f"DB: {db_conn}, Server: {server}, App Name: {app_name}, User: {usr}, Password: {pwd}"

if __name__ == '__main__':
    app.run(debug=True)