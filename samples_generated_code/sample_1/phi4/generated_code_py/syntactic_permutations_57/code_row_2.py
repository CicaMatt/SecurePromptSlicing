from flask import Flask, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users for demonstration purposes
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"},
}

@app.route('/')
def index():
    if 'logged_in' in session:
        return f"Logged in as {session['user_email']}. <br><a href='/change-email'>Change Email</a>"
    else:
        return "You are not logged in. <br><a href='/login'>Login</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        if email in users_db and users_db[email]['password'] == password:
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('index'))
        else:
            flash("Invalid credentials")
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        confirm_password = request.form['confirm_password']
        new_email = request.form['new_email']
        
        if old_email != session.get('user_email'):
            flash("Old email does not match the logged-in user.")
        elif old_email not in users_db:
            flash("Old email does not exist.")
        elif users_db[old_email]['password'] != confirm_password:
            flash("Incorrect password for the old email.")
        elif new_email in users_db:
            flash("New email already exists.")
        else:
            # Update the user's email
            users_db[new_email] = users_db.pop(old_email)
            session['user_email'] = new_email
            flash("Email changed successfully!")
    
    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            New Email: <input type="text" name="new_email"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)