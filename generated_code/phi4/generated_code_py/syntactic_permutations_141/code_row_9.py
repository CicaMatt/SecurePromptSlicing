from flask import Flask

app = Flask(__name__)

def get_server_name():
    def return_server_name():
        return "my_server_name"
    return return_server_name

def get_database_name():
    def return_database_name():
        return "my_database_name"
    return return_database_name

def get_database_user():
    def return_database_user():
        return "my_database_user"
    return return_database_user

def get_database_password():
    def return_database_password():
        return "my_secure_password"
    return return_database_password

@app.route('/')
def index():
    server_name_func = get_server_name()
    database_name_func = get_database_name()
    database_user_func = get_database_user()
    database_password_func = get_database_password()

    return f"Server: {server_name_func()}, Database: {database_name_func()}, User: {database_user_func()}, Password: {database_password_func()}"

if __name__ == '__main__':
    app.run(debug=True)