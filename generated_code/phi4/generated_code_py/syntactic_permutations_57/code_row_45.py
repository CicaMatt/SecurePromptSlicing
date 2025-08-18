from flask import Flask, request, redirect, url_for, flash, session
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# In-memory storage for demonstration purposes
users_db = {
    "user@example.com": {"password_hash": generate_password_hash("password123"), "email": "user@example.com"}
}

def authenticate(email, password):
    user = users_db.get(email)
    if user and check_password_hash(user["password_hash"], password):
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if authenticate(email, password):
            session['user_email'] = email
            flash('You were logged in successfully!', 'success')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials', 'danger')
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = session['user_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        if user and check_password_hash(user["password_hash"], confirm_password):
            if new_email in users_db:
                flash('New email already exists.', 'danger')
            else:
                # Change the user's email
                del users_db[old_email]
                users_db[new_email] = {"email": new_email, "password_hash": user["password_hash"]}
                session['user_email'] = new_email
                flash('Email changed successfully!', 'success')
        else:
            flash('Incorrect password.', 'danger')

    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    flash('You were logged out.', 'success')
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)