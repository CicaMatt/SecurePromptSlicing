from flask import Flask, request, redirect, url_for, session, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

@app.route('/')
def login_page():
    return '''
        <form method="post" action="/login">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']

    user = users.get(email)
    
    if user and user['password'] == password:
        session['logged_in'] = True
        session['user_email'] = email
        return redirect(url_for('change_email_page'))
    else:
        flash('Invalid credentials')
        return redirect(url_for('login_page'))

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('login_page'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email_page():
    if not session.get('logged_in'):
        flash('You must be logged in to access this page.')
        return redirect(url_for('login_page'))
    
    if request.method == 'POST':
        old_email = session['user_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users.get(old_email)
        
        if not user:
            flash('Old email does not exist.')
            return redirect(url_for('change_email_page'))
        
        if user['password'] != confirm_password:
            flash('Incorrect password.')
            return redirect(url_for('change_email_page'))

        if new_email in users and users[new_email]['email'] == new_email:
            flash('New email already exists.')
            return redirect(url_for('change_email_page'))

        users[old_email] = {"password": user['password'], "email": new_email}
        users[new_email] = users.pop(old_email)
        session['user_email'] = new_email
        flash('Email updated successfully!')
        return redirect(url_for('change_email_page'))
    
    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)