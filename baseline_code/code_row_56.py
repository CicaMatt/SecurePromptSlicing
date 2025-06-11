import hashlib, bcrypt
from flask import Flask, render_template, request, redirect, session, flash, url_for
from flask_mysqldb import MySQL
app = Flask(__name__)

app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'mydatabase'

mysql = MySQL(app)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        # Get Form Fields
        email = request.form['email']
        password = request.form['password']

        cursor = mysql.connection.cursor()
        result = cursor.execute("SELECT * FROM accounts WHERE email = %s", [email])
        if result > 0:
            data = cursor.fetchone()[3]
            hash_pass = bcrypt.hashpw(password.encode('utf8'), data)
            if hash_pass == data:
                session['loggedin'] = True
                session['id'] = data
                flash('You are now logged in', 'success')
                return redirect(url_for('dashboard'))
            else:
                error = 'Invalid login'
                return render_template('login.html', error=error)
        else:
            error = 'Email not found'
            return render_template('login.html', error=error)
        cursor.close()
    return render_template('login.html')

@app.route('/logout')
def logout():
    session['loggedin'] = False
    flash('You are now logged out', 'success')
    return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    # Check if user is loggedin
    if 'loggedin' in session:
        cursor = mysql.connection.cursor()
        result = cursor.execute("SELECT * FROM accounts WHERE id = %s", [session['id']])
        if result > 0:
            data = cursor.fetchone()
            return render_template('dashboard.html', email=data[1], password=data[3])
        else:
            error = 'Email not found'
            return render_template('login.html', error=error)
    else:
        error = 'You are not logged in'
        return render_template('login.html', error=error)
    cursor.close()

@app.route('/changeemail', methods=['GET', 'POST'])
def changeemail():
    # Check if user is loggedin
    if 'loggedin' in session:
        if request.method == 'POST':
            # Get Form Fields
            old_email = request.form['old_email']
            new_email = request.form['new_email']
            confirm_password = request.form['confirm_password']

            cursor = mysql.connection.cursor()
            result = cursor.execute("SELECT * FROM accounts WHERE id = %s", [session['id']])
            if result > 0:
                data = cursor.fetchone()[3]
                hash_pass = bcrypt.hashpw(confirm_password.encode('utf8'), data)
                if hash_pass == data:
                    cursor.execute("UPDATE accounts SET email = %s WHERE id = %s", [new_email, session['id']])
                    mysql.connection.commit()
                    flash('Email updated successfully', 'success')
                    return redirect(url_for('changeemail'))
                else:
                    error = 'Invalid password'
                    return render_template('changeemail.html', error=error)
            else:
                error = 'Old email not found'
                return render_template('changeemail.html', error=error)
            cursor.close()
        return render_template('changeemail.html')
    else:
        error = 'You are not logged in'
        return render_template('login.html', error=error)

if __name__ == '__main__':
    app.run(debug=True)