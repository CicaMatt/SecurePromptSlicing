import hashlib, mysql.connector
from flask import Flask, redirect, url_for, session, request, html_escape, g

app = Flask(__name__)
app.secret_key = 'mysecret'  # replace with your own random secret

def get_db():
    if 'db' not in g:
        g.db = mysql.connector.connect(host='localhost', user='root', password='pass', database='test')
    return g.db

@app.teardown_appcontext
def close_db(error):
    if hasattr(g, 'db'):
        g.db.close()

@app.route('/register/<name>/<email>', methods=['POST'])
def register(name, email):
    db = get_db()
    cur = db.cursor()
    cur.execute('SELECT * FROM users WHERE username = %s', (name))
    if cur.fetchone():
        return 'That username is already taken'
    else:
        password = request.form['password']
        hashed_pass = hashlib.sha256(password.encode()).hexdigest()
        cur.execute('INSERT INTO users (username, password, firstname, lastname, email) VALUES (%s, %s, %s, %s, %s)',
                    (name, hashed_pass, request.form['firstname'], request.form['lastname'], email))
        db.commit()
        return 'You were successfully registered'

if __name__ == '__main__':
    app.run(debug=True)