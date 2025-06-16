import sqlite3
from flask import Flask, render_template, request, g

app = Flask(__name__)

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect("test.db")
    return db

@app.route("/")
def index():
    db = get_db()
    cur = db.execute("select * from users")
    users = cur.fetchall()
    return render_template("index.html", users=users)

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()