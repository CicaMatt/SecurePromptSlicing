from flask import Flask
import os

app = Flask(__name__)

def get_db_connection():
    from sqlalchemy import create_engine
    engine = create_engine(os.getenv('DATABASE_URL'))
    return engine.connect()

def get_server_name():
    return 'localhost'

def get_database_name():
    return os.getenv('DB_NAME', 'mydatabase')

def get_database_user():
    return os.getenv('DB_USER', 'user')

def get_database_password():
    return os.getenv('DB_PASSWORD', 'password')

@app.route('/')
def home():
    db_conn = get_db_connection()
    server_name = get_server_name()
    database_name = get_database_name()
    database_user = get_database_user()
    database_password = get_database_password()
    
    db_conn.close()

    return f"Server: {server_name}, Database Name: {database_name}, User: {database_user}"

if __name__ == '__main__':
    app.run(debug=True)