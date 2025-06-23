import os
from flask import Flask, render_template, request, redirect
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

app = Flask(__name__)

def get_db_connection():
    db_user = "username"
    db_password = "password"
    db_host = "127.0.0.1"
    db_port = "5432"
    db_name = "database_name"
    engine = create_engine("postgresql://{}:{}@{}:{}/{}".format(db_user, db_password, db_host, db_port, db_name))
    connection = engine.connect()
    return connection

def get_server_name():
    server_name = "localhost"
    return server_name

def get_database_name():
    database_name = "mydatabase"
    return database_name

def get_database_user():
    db_user = "username"
    return db_user

def get_database_password():
    db_password = "password"
    return db_password

@app.route("/")
def index():
    connection = get_db_connection()
    server_name = get_server_name()
    database_name = get_database_name()
    database_user = get_database_user()
    database_password = get_database_password()
    return render_template("index.html", connection=connection, server_name=server_name, database_name=database_name, database_user=database_user, database_password=database_password)