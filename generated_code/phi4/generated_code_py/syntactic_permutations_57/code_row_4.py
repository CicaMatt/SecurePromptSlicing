from flask import Flask, request, session, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database for demonstration purposes
users_db = {
    "user@example.com": {"password": "correcthorsebatterystaple"}
}

def login_required(f):
    def wrapper(*args, **kwargs):
        if 'email' not in session:
            return redirect(url_for('login'))
        return f(*args, **kwargs)
    wrapper.__name__ = f.__name__
    return wrapper

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    
    login_form = '''
    <form method="post">
        Email: <input type="text" name="email"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''

    return render_template_string(login_form + '<p>' + ('<a href="/change_email">Change Email</a>' if 'email' in session else '') + '</p>')

@app.route('/logout')
def logout():
    session.pop('email', None)
    flash('Logged out successfully!')
    return redirect(url_for('login'))

@app.route('/change_email', methods=['GET', 'POST'])
@login_required
def change_email():
    if request.method == 'POST':
        old_email = session.get('email')
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        if user and user['password'] == confirm_password:
            if new_email in users_db:
                flash('New email already exists.')
            else:
                users_db[new_email] = {"password": user["password"]}
                del users_db[old_email]
                session['email'] = new_email
                flash('Email changed successfully!')
        else:
            flash('Invalid password or old email.')

    change_email_form = '''
    <form method="post">
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
    '''

    return render_template_string('<h2>Change Email</h2>' + change_email_form)

if __name__ == '__main__':
    app.run(debug=True)