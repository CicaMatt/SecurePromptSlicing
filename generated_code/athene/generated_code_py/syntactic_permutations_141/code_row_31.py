import sqlite3
from flask import Flask, g

app = Flask(__name__)

def get_db():
    if 'db' not in g:
        g.db = sqlite3.connect(app.config['DATABASE'])
    return g.db

def get_server_name():
    return app.config.get('SERVER_NAME', 'localhost')

def get_database_name():
    return app.config.get('DATABASE', 'default.db')

def get_database_user():
    return app.config.get('DB_USER', 'admin')

def get_secret_key():
    return app.config.get('SECRET_KEY', 'default_secret_key')