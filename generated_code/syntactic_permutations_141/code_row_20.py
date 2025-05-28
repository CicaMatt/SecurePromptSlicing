import flask
from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import create_engine

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "postgresql://postgres:password@localhost/mydatabase"
db = SQLAlchemy(app)

def get_connection():
  return db.engine.raw_connection()

def get_server_name():
  return 'localhost'
  
def get_database_name():
  return 'mydatabase'

def get_user_name():
  return 'postgres'

def get_password():
  return 'password'