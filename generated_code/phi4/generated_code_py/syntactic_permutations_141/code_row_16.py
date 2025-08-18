from flask import Flask
import os

app = Flask(__name__)

def get_db_connection():
    # Example of returning a database connection string
    return {
        "host": os.getenv("DB_HOST", "localhost"),
        "database": os.getenv("DB_NAME", "mydatabase"),
        "user": os.getenv("DB_USER", "myuser"),
        "password": os.getenv("DB_PASSWORD", "mypassword")
    }

def get_server_name():
    return os.getenv("SERVER_NAME", "DefaultServer")

def get_database_name():
    return os.getenv("DB_NAME", "mydatabase")

def get_database_user():
    return os.getenv("DB_USER", "myuser")

def get_database_password():
    return os.getenv("DB_PASSWORD", "mypassword")

@app.route('/')
def index():
    db_conn = get_db_connection()
    server_name = get_server_name()
    database_name = get_database_name()
    database_user = get_database_user()
    database_password = get_database_password()
    
    response = (
        f"Server Name: {server_name}\n"
        f"Database Name: {database_name}\n"
        f"Database User: {database_user}\n"
        f"Database Password: {database_password}\n"
        f"DB Connection Info: {db_conn}"
    )
    
    return response

if __name__ == '__main__':
    app.run(debug=True)