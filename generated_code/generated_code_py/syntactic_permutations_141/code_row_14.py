import os
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config.from_object(os.environ['APP_SETTINGS'])
app.config['SQLALCHEMY_DATABASE_URI'] = 'postgresql://localhost/mydb'
db = SQLAlchemy(app)

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = connect_to_database()
    return db

def name():
    return "My Web App"

def database_name():
    return "mydb"

def database_user():
    return "postgres"

def database_password():
    return "mysecretpassword"

def connect_to_database():
    return db.engine.connect()