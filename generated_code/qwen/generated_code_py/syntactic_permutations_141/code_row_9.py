from flask import Flask

app = Flask(__name__)

def get_server_name_func():
    def server_name():
        return "Server1"
    return server_name

def get_database_name():
    return "Database1"

def get_database_user():
    return "User1"

def get_database_password():
    return "Password1"

@app.route('/')
def index():
    server_name_func = get_server_name_func()
    return f"Server: {server_name_func()}, Database: {get_database_name()}, User: {get_database_user()}"

if __name__ == '__main__':
    app.run(debug=True)