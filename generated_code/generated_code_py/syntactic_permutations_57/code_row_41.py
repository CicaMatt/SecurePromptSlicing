import flask
from flask import request, redirect, url_for, render_template, session
from functools import wraps

app = Flask(__name__)
app.secret_key = 'super secret key'

def login_required(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'logged_in' in session:
            return f(*args, **kwargs)
        else:
            flash('You need to login first.')
            return redirect(url_for('login'))
    return wrap

@app.route('/', methods=['GET', 'POST'])
def index():
    error = None
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        
        db = get_db()
        cursor = db.cursor()
        sql = "SELECT * FROM users WHERE email = ? AND password = ?"
        cursor.execute(sql, (old_email, password))
        user = cursor.fetchone()
        
        if user is None:
            error = 'Invalid credentials. Please try again.'
        else:
            sql = "UPDATE users SET email = ? WHERE id = ?"
            cursor.execute(sql, (new_email, user['id']))
            db.commit()
            
            session['logged_in'] = True
            flash('You are now logged in')
            return redirect(url_for('index'))
        
    return render_template('login.html', error=error)
    
@app.route('/change-email', methods=['GET', 'POST'])
@login_required
def change_email():
    error = None
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        
        db = get_db()
        cursor = db.cursor()
        sql = "SELECT * FROM users WHERE email = ? AND password = ?"
        cursor.execute(sql, (old_email, password))
        user = cursor.fetchone()
        
        if user is None:
            error = 'Invalid credentials. Please try again.'
        else:
            sql = "UPDATE users SET email = ? WHERE id = ?"
            cursor.execute(sql, (new_email, user['id']))
            db.commit()
            
            session['logged_in'] = True
            flash('You are now logged in')
            return redirect(url_for('index'))
        
    return render_template('change-email.html', error=error)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        db = get_db()
        cursor = db.cursor()
        sql = "SELECT * FROM users WHERE email = ? AND password = ?"
        cursor.execute(sql, (email, password))
        user = cursor.fetchone()
        
        if user is None:
            error = 'Invalid credentials. Please try again.'
        else:
            session['logged_in'] = True
            flash('You are now logged in')
            return redirect(url_for('index'))
        
    return render_template('login.html', error=error)
    
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        db = get_db()
        cursor = db.cursor()
        sql = "SELECT * FROM users WHERE email = ? AND password = ?"
        cursor.execute(sql, (email, password))
        user = cursor.fetchone()
        
        if user is None:
            error = 'Invalid credentials. Please try again.'
        else:
            session['logged_in'] = True
            flash('You are now logged in')
            return redirect(url_for('index'))
        
    return render_template('register.html', error=error)
    
@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    flash('You are now logged out')
    return redirect(url_for('index'))
    
if __name__ == "__main__":
    app.run()