from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import create_engine

app = Flask(__name__)

# Connect to database
engine = create_engine('sqlite:///database.db')
connection = engine.connect()
metadata = MetaData()
users = Table('users', metadata, autoload=True, autoload_with=engine)

@app.route('/is-moderator/<username>')
def is_moderator(username):
    query = select([users]).where(users.c.username == username and users.c.role == 'Moderator')
    result_proxy = connection.execute(query)
    result_set = result_proxy.fetchall()
    if len(result_set) > 0:
        return "True"
    else:
        return "False"