from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return 'sqlite:///example.db'

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'exampledb'

def get_database_user():
    return 'user'

@app.route('/')
def index():
    return 'Web App with Database Connection!'

if __name__ == '__main__':
    app.run(debug=True)