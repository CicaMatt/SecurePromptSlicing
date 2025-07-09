import flask
from flask import request, render_template

@app.route('/login', methods=['POST'])
def check():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        with sqlite3.connect('database.db') as db:
            cur = db.cursor()
            cur.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password))
            if cur.fetchone():
                return render_template('home.html')
            else:
                return render_template('login.html', message='Invalid credentials')
    return render_template('login.html')