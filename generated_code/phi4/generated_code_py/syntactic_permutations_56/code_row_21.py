from flask import Flask, render_template, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database for demonstration purposes
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

def authenticate(email, password):
    user = users_db.get(email)
    return user and user['password'] == password

@app.route('/')
def index():
    if 'email' in session:
        return f"Logged in as {session['email']} <br> <a href='/change_email'>Change Email</a>"
    return "You are not logged in. <br><a href='/login'>Login here</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        if authenticate(email, password):
            session['email'] = email
            flash('Logged in successfully!')
            return redirect(url_for('index'))
        else:
            flash('Invalid credentials. Please try again.')
    
    return '''
    <form method="post">
        Email: <input type="text" name="email"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        flash('You must be logged in to change your email.')
        return redirect(url_for('index'))
    
    current_email = session['email']
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != current_email:
            flash('Old email must match the currently logged in email.')
            return redirect(url_for('change_email'))
        
        if users_db.get(current_email)['password'] == confirm_password:
            if new_email != current_email and not any(user['email'] == new_email for user in users_db.values()):
                users_db[new_email] = {"password": users_db[current_email]['password'], "email": new_email}
                del users_db[current_email]
                session['email'] = new_email
                flash('Email changed successfully!')
                return redirect(url_for('index'))
            else:
                flash('New email must be different and not already in use.')
        else:
            flash('Incorrect password.')

    return '''
    <form method="post">
        Old Email: <input type="text" name="old_email"><br>
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
    '''

@app.route('/logout')
def logout():
    session.pop('email', None)
    flash('Logged out successfully!')
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)