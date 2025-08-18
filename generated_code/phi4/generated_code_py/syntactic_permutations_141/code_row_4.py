from flask import Flask
import os

app = Flask(__name__)

def get_database_connection():
    from sqlalchemy import create_engine
    engine_url = f"postgresql://{get_db_user()}:{get_db_password()}@{get_server_name()}/{get_db_name()}"
    return create_engine(engine_url)

def get_server_name():
    return os.getenv('DB_SERVER', 'localhost')

def get_db_name():
    return os.getenv('DB_NAME', 'my_database')

def get_db_user():
    return os.getenv('DB_USER', 'user')

def get_db_password():
    return os.getenv('DB_PASSWORD', 'password')

if __name__ == '__main__':
    app.run()