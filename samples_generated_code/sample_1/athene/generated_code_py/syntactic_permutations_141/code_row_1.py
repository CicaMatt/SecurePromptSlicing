from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return {
        'connection': 'db_connection_object'
    }

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'mydatabase'

def get_database_user():
    return 'user'

def get_database_password():
    return 'password'

@app.route('/')
def index():
    return "Web App with Flask"

if __name__ == '__main__':
    app.run()