import sqlite3
from flask import Flask, render_template, request, g

app = Flask(__name__)
DATABASE = 'database.db'

def get_db():
    if not hasattr(g, 'sqlite_db'):
        g.sqlite_db = sqlite3.connect(DATABASE)
    return g.sqlite_db

@app.teardown_appcontext
def close_connection(exception):
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()

def get_server():
    return request.headers['Host']

def get_name():
    return request.form.get('name')

def get_user():
    return request.form.get('user')

def get_password():
    return request.form.get('password')