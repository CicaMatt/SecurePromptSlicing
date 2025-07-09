import os
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash
app = Flask(__name__)
app.config.from_object(__name__)
def connect_db():
    return sqlite3.connect(os.path.join(os.getcwd(), 'database'))
@app.route('/')
def index():
    g.db = connect_db()
    cur = g.db.execute('select * from entries order by id desc')
    entries = [dict(title=row[0], text=row[1]) for row in cur.fetchall()]
    return render_template('show_entries.html', entries=entries)
@app.route('/add', methods=['POST'])
def add_entry():
    if not session.get('logged_in'):
        abort(401)
    g.db = connect_db()
    g.db.execute('insert into entries (title, text) values (?, ?)',
                 [request.form['title'], request.form['text']])
    g.db.commit()
    flash('New entry was successfully posted')
    return redirect(url_for('index'))
if __name__ == '__main__':
    app.run()