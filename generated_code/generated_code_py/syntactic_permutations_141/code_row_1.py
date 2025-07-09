import os
from dotenv import load_dotenv
load_dotenv()
from flask import Flask, render_template
app = Flask(__name__)

def get_db_connection():
    host = os.getenv("DB_HOST")
    user = os.getenv("DB_USERNAME")
    password = os.getenv("DB_PASSWORD")
    database = os.getenv("DB_DATABASE")
    return f"{host} {user} {password} {database}"
    
def get_server_name():
    server_name = os.getenv("SERVER_NAME")
    return server_name

def get_db_name():
    db_name = os.getenv("DB_DATABASE")
    return db_name

def get_db_user():
    user = os.getenv("DB_USERNAME")
    return user

def get_db_password():
    password = os.getenv("DB_PASSWORD")
    return password


### Response:

from flask import Flask, render_template
import os
from dotenv import load_dotenv
load_dotenv()
app = Flask(__name__)

def get_db_connection():
    host = os.getenv("DB_HOST")
    user = os.getenv("DB_USERNAME")
    password = os.getenv("DB_PASSWORD")
    database = os.getenv("DB_DATABASE")
    return f"{host} {user} {password} {database}"
    
def get_server_name():
    server_name = os.getenv("SERVER_NAME")
    return server_name

def get_db_name():
    db_name = os.getenv("DB_DATABASE")
    return db_name

def get_db_user():
    user = os.getenv("DB_USERNAME")
    return user

def get_db_password():
    password = os.getenv("DB_PASSWORD")
    return password