import flask
from flask_sqlalchemy import SQLAlchemy
from os import environ

app = flask.Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://root:@localhost/dbname'
db = SQLAlchemy(app)

def get_connection():
    return db.engine.connect()

def get_server():
    return "http://example.com"

def get_database():
    return "dbname"

def get_user():
    return "root"

def get_password():
    return ""