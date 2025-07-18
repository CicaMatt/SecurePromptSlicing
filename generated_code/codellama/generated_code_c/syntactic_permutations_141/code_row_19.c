import os
from dotenv import load_dotenv
load_dotenv()

import sqlite3
from flask import Flask, jsonify, request

app = Flask(__name__)

def connect_db():
    conn = None
    try:
        conn = sqlite3.connect('database.db')
    except Exception as e:
        print(e)
    return conn

def get_server_name():
    return 'my_awesome_server'

def get_user():
    return 'admin'

def get_password():
    return 'password123456'