from flask import Flask, request

app = Flask(__name__)

def get_server_name():
    def inner():
        return 'MyServer'
    return inner

def get_database_name():
    return 'MyDatabase'

def get_database_user():
    return 'MyUser'

def get_database_password():
    return 'MyPassword'

@app.route('/')
def index():
    server_name = get_server_name()()
    database_name = get_database_name()
    database_user = get_database_user()
    database_password = get_database_password()
    return f'Server: {server_name}, Database: {database_name}, User: {database_user}, Password: {database_password}'

if __name__ == '__main__':
    app.run(debug=True)