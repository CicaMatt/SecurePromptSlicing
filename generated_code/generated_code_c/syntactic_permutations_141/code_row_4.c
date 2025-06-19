import os
from flask import Flask, request, g, redirect, url_for, abort, render_template

app = Flask(__name__)

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect('test.db')
    return db

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()

def get_server():
    return 'https://www.example.com'

def get_dbname():
    return 'test'

def get_username():
    return 'user123'

def get_password():
    return 'pass456'