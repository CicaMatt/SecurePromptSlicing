import os
from flask import Flask, render_template

app = Flask(__name__)

def get_db():
    # create and return a connection to database.
    pass

def get_server_name():
    # return the server name of your app
    return 'https://my-flask-app.herokuapp.com'

def get_db_name():
    # return the database name
    return os.environ['DB_NAME']

def get_db_user():
    # return the database user name
    return os.environ['DB_USER']