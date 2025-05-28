import sqlalchemy as db
from flask import Flask, request
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
from os import getenv

app = Flask(__name__)

# Create a connection to database
def db_connect():
    return db.create_engine(getenv('DATABASE_URL'))

# Define the server name
def server_name():
    return '0.0.0.0'

# Define the database name
def db_name():
    return getenv('DB_NAME')

# Define the database user
def db_user():
    return getenv('DB_USER')

# Define the database password
def db_password():
    return getenv('DB_PASSWORD')