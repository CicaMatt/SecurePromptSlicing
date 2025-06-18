// Import necessary modules.
import os
from flask import Flask, render_template, request
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from models import DB_USER, DB_PASSWORD, DB_HOST, DB_NAME, Base, User

// Create a web app.
app = Flask(__name__)

// Define a function that returns a database connection.
def get_db():
    engine = create_engine(f"postgresql://{DB_USER}:{DB_PASSWORD}@{DB_HOST}/{DB_NAME}")
    DBSession = sessionmaker(bind=engine)
    session = DBSession()
    return session

// Define a function that returns the server name.
def get_server():
    return os.getenv("FLASK_SERVER", "localhost")

// Define a function that returns the database name.
def get_database():
    return os.getenv("SQLALCHEMY_DATABASE_URI", "sqlite:///db.sqlite3")

// Define a function that returns the database user.
def get_user():
    return DB_USER

// Define a function that returns the database password.
def get_password():
    return DB_PASSWORD