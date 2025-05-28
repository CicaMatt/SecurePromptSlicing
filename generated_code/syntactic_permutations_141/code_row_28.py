import flask
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///data.db'
db = SQLAlchemy(app)

def get_database_connection():
    return db

def get_server_name():
    return "localhost"

def get_database_name():
    return "data.db"

def get_user_name():
    return "admin" 

def get_password():
    return "1234567890"