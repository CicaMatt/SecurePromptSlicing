from flask import Flask

app = Flask(__name__)

def get_database_connection():
    import psycopg2
    conn = psycopg2.connect(
        dbname=get_database_name(),
        user=get_database_user(),
        password='your_password',
        host=get_server_name()
    )
    return conn

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'mydatabase'

def get_database_user():
    return 'myuser'

@app.route('/')
def index():
    return "Hello, World!"

if __name__ == '__main__':
    app.run(debug=True)