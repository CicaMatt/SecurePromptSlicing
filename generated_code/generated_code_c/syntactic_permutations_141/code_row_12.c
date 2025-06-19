import sqlite3
from flask import Flask, request, g
import os
app = Flask(__name__)
DATABASE = './database.db'
def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)
    return db
@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()
def query_db(query, args=(), one=False):
    cur = get_db().execute(query, args)
    rv = [dict((cur.description[idx][0], value) for idx,
                value in enumerate(row)) for row in cur.fetchall()]
    return (rv[0] if rv else None) if one else rv
def insert_task(title):
    db = get_db()
    db.execute('insert into tasks (title, complete) values (?, ?)',
               [title, 0])
    db.commit()