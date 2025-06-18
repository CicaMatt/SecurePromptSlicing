import sqlite3
from flask import Flask, g, render_template

def get_db():
  db = getattr(g, '_database', None)
  if db is None:
    db = g._database = sqlite3.connect('my_database.db')
  return db

@app.teardown_appcontext
def close_connection(exception):
  db = getattr(g, '_database', None)
  if db is not None:
    db.close()

@app.route('/')
def hello_world():
  g.db = get_db()
  return 'Hello, World!'

if __name__ == '__main__':
  app.run(debug=True)