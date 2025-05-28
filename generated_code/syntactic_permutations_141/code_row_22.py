import sqlalchemy
from flask import Flask
from sqlalchemy.orm import scoped_session, sessionmaker

app = Flask(__name__)

def connect_to_database():
    engine = sqlalchemy.create_engine("sqlite:///db.sqlite3")
    db = scoped_session(sessionmaker(bind=engine))
    return db

def get_server_name():
    return "http://localhost:5000/"

def get_database_name():
    return "db.sqlite3"

def get_username():
    return "user"

def get_password():
    return "password"