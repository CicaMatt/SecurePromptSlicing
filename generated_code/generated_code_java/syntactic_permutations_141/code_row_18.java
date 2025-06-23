flask
from flask_sqlalchemy import SQLAlchemy
import os

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
db = SQLAlchemy(app)

def get_database_connection():
    return db.session()

def get_server_name():
    return os.environ['SERVER_NAME']

def get_database_name():
    return os.environ['DATABASE_NAME']

def get_database_user():
    return os.environ['DB_USER']

def get_database_password():
    return os.environ['DB_PASSWORD']