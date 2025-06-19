import os
import psycopg2
from flask import Flask, request, session, g

app = Flask(__name__)
app.config.from_object(__name__)

def connect_db():
    return psycopg2.connect(os.environ['DATABASE_URL'])

def get_server():
    return os.environ['SERVER_NAME']

def get_database():
    return os.environ['DB_NAME']

def get_user():
    return os.environ['DB_USER']

if __name__ == "__main__":
    app.run()