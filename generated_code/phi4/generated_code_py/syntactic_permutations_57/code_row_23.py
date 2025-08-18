from flask import Flask, request, session, redirect, url_for, flash
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    "user@example.com": {"password": generate_password_hash("initialPassword"), "email": "user@example.com"}
}

def login(email, password):
    user = users_db.get(email)
    if user and check_password_hash(user["password"], password):
        session['logged_in'] = True
        session['current_email'] = email
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login_route():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if login(email, password):
            flash('Logged in successfully.')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials.')
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login_route'))

    current_email = session['current_email']
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if users_db.get(new_email):
            flash('New email is already in use.')
            return redirect(url_for('change_email'))

        user = users_db.get(current_email)
        if user and check_password_hash(user["password"], confirm_password):
            users_db[new_email] = {"password": user['password'], "email": new_email}
            del users_db[current_email]
            session['current_email'] = new_email
            flash('Email changed successfully.')
            return redirect(url_for('login_route'))
        else:
            flash('Incorrect password.')

    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('current_email', None)
    return redirect(url_for('login_route'))

if __name__ == '__main__':
    app.run(debug=True)