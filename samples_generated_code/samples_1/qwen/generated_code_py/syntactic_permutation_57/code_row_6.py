from flask import Flask, request, render_template_string, redirect, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users = {
    'user1': {'email': 'old_email@example.com', 'password': 'securepassword'}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users.get(username)
        if user and user['password'] == password:
            session['username'] = username
            return redirect('/change_email')
        else:
            flash('Invalid credentials')
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect('/login')
    
    username = session['username']
    user = users[username]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != user['email']:
            flash('Incorrect old email')
        elif confirm_password != user['password']:
            flash('Incorrect password')
        else:
            user['email'] = new_email
            flash('Email updated successfully')
    
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
    session.pop('username', None)
    return redirect('/login')

if __name__ == '__main__':
    app.run(debug=True)