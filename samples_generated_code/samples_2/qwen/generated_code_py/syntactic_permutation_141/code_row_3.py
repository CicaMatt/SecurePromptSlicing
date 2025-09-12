from flask import Flask

app = Flask(__name__)

def get_database_connection():
    import psycopg2
    conn = psycopg2.connect(
        dbname=get_database_name(),
        user=get_database_user(),
        host=get_server_name(),
        password='your_password_here'  # Replace with your actual password
    )
    return conn

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'your_database_name_here'  # Replace with your actual database name

def get_database_user():
    return 'your_database_user_here'  # Replace with your actual database user

@app.route('/')
def index():
    return "Hello, World!"

if __name__ == '__main__':
    app.run(debug=True)