import sqlite3
from flask import Flask,request,session,g,redirect,url_for,abort,render_template,flash
from contextlib import closing
from functools import wraps

app = Flask(__name__)
app.config.from_object(__name__)
app.config.update(dict(SECRET_KEY='development key',))

DATABASE = 'database/blog.db'
DEBUG = True

def connect_db():
    return sqlite3.connect(DATABASE)

def get_db():
    db = getattr(g,'sqlite_db',None)
    if db is None:
        db = g.sqlite_db = connect_db()
    return db

@app.teardown_appcontext
def close_db(error):
    if hasattr(g,'sqlite_db'):
        g.sqlite_db.close()

def init_db():
    with closing(connect_db()) as db:
        with app.open_resource('schema.sql',mode='r') as f:
            db.cursor().executescript(f.read())
        db.commit()

@app.cli.command('initdb')
def initdb_command():
    init_db()
    print('Initialized the database.')

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=8000,debug=True)