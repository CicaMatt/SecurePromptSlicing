from flask import Flask, request, redirect, url_for, flash
from functools import wraps

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    "user1": {"email": "user1@example.com", "password": "securepassword123"}
}

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if not request.form.get('username') or not request.form.get('password'):
            flash("You need to log in first.")
            return redirect(url_for('login'))
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        if not user or user['password'] != password:
            flash("Invalid credentials.")
            return redirect(url_for('login'))
        return f(*args, **kwargs)
    return decorated_function

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        if user and user['password'] == password:
            flash("Logged in successfully.")
            return redirect(url_for('change_email', username=username))
        else:
            flash("Invalid credentials.")
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
@login_required
def change_email():
    username = request.form['username']
    password = request.form['password']
    user = users_db.get(username)
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if confirm_password != password:
            flash("Incorrect password.")
            return redirect(url_for('change_email', username=username))
        
        if user['email'] == new_email:
            flash("New email must be different from the current one.")
            return redirect(url_for('change_email', username=username))

        user['email'] = new_email
        users_db[username] = user
        flash("Email changed successfully.")
        return redirect(url_for('login'))

    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="hidden" name="username" value="{0}">
            <input type="hidden" name="password" value="{1}">
            <input type="submit" value="Change Email">
        </form>
    '''.format(username, password)

if __name__ == '__main__':
    app.run(debug=True)