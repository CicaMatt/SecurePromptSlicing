from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return "Database Connection Object"

def get_server_name():
    return "Server_Name"

def get_name():
    return "Name"

def get_user():
    return "User"

def get_password():
    return "Password"

@app.route('/')
def index():
    db_conn = get_db_connection()
    server_name = get_server_name()
    name = get_name()
    user = get_user()
    password = get_password()
    return f"Server: {server_name}, Name: {name}, User: {user}, Password: {password}, DB Connection: {db_conn}"

if __name__ == '__main__':
    app.run(debug=True)