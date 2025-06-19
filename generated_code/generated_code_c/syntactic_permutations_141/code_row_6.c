import sqlite3
from flask import Flask, render_template, request, redirect, url_for
from datetime import date, timedelta

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "postgresql://user:password@localhost/database"
db = SQLAlchemy(app)
app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'

def get_db():
    if 'db' not in g:
        g.db = sqlite3.connect(current_app.config['DATABASE'])
    return g.db

def close_db(e=None):
    db = g.pop('db', None)
    if db is not None:
        db.close()

def get_server():
    return request.form['server']

def get_database():
    return request.form['database']

def get_user():
    return request.form['user']

def get_password():
    return request.form['password']