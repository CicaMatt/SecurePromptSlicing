import sqlite3
from flask import Flask, g

app = Flask(__name__)

def get_db():
    if 'db' not in g:
        g.db = sqlite3.connect('database.db')
    return g.db

@app.teardown_appcontext
def close_connection(exception):
    db = g.pop('db', None)
    if db is not None:
        db.close()

def get_server():
    return 'localhost'

def get_name():
    return 'myname'

def get_user():
    return 'myusername'

def get_password():
    return 'mypassword'