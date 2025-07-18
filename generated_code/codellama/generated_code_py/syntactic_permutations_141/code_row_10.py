import sqlite3
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash

app = Flask(__name__)

def get_connection():
    # Return a new connection to the SQLite database.
    return sqlite3.connect('todoism.db')

@app.teardown_appcontext
def close_connection(exception):
    # Close the database again at the end of the request.
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()
        
def get_server():
    return 'localhost'
    
@app.route('/')
def index():
    g.db = get_connection()
    cur = g.db.execute('select task from tasks order by create_date desc')
    tasks = [dict(title=row[0]) for row in cur.fetchall()]
    g.db.close()
    return render_template('index.html', tasks=tasks)
    
@app.route('/add', methods=['POST'])
def add():
    task = request.form['task']
    server_name = get_server()
    g.db = get_connection()
    try:
        g.db.execute('insert into tasks (title, status) values (?, ?)', [task, 'active'])
        g.db.commit()
        flash('New entry was successfully posted')
    except sqlite3.Error as e:
        flash(e.args[0])
    finally:
        g.db.close()
    return redirect('/')