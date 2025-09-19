from flask import Flask, request, session, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database for demonstration purposes
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid login credentials!')
    
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
        return redirect(url_for('login'))
    
    user_email = session['user_email']
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != user_email:
            flash('Old email does not match current login.')
        elif new_email in users_db and users_db[new_email]['password'] == users_db[old_email]['password']:
            flash('New email already exists.')
        elif confirm_password != users_db[user_email]['password']:
            flash('Incorrect password!')
        else:
            users_db[new_email] = {"password": users_db[user_email]['password'], "email": new_email}
            del users_db[old_email]
            session['user_email'] = new_email
            flash('Email changed successfully!')
            return redirect(url_for('change_email'))
    
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
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)