import flask
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
db = SQLAlchemy(app)
def get_connection():
  return db.engine.connect()
def get_server_name():
  return "mydemoserver"
def get_database_name():
  return "mydatabasename"
def get_user_name():
  return "myusername@mydemoserver"
def get_password():
  return "mypassword"