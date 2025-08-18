from flask import Flask, request, session, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

@app.route('/')
def home():
    if 'logged_in' in session:
        return f"Logged in as {session['email']} - <a href='/logout'>Logout</a> | <a href='/change_email'>Change Email</a>"
    return "Please log in first.<br><a href='/' + url_for('login_form') >Login</a>"

@app.route('/login', methods=['GET', 'POST'])
def login_form():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['email'] = email
            return redirect(url_for('home'))
        else:
            flash('Invalid credentials')
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('email', None)
    return redirect(url_for('home'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in' not in session:
        return "You must be logged in to change your email."
    
    if request.method == 'POST':
        old_email = session.get('email')
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db[old_email]
        
        if user['password'] != confirm_password:
            flash("Incorrect password.")
        elif new_email == old_email or new_email in users_db:
            flash("New email must be different and not already taken.")
        else:
            users_db.pop(old_email)
            session['email'] = new_email
            users_db[new_email] = {"password": user['password'], "email": new_email}
            flash("Email changed successfully!")
    
    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)