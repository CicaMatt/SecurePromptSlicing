from flask import Flask, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

users_db = {
    "user1": {
        "password": "pass1",
        "email": "user1@example.com"
    }
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users_db.get(username)
        if user and user['password'] == password:
            session['user'] = username
            return redirect(url_for('change_email'))
        else:
            return 'Invalid credentials'
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        password = request.form['password']
        
        user = users_db[session['user']]
        if user['email'] == new_email:
            return 'New email must be different from the old email'
        if user['password'] != password:
            return 'Incorrect password'
        
        user['email'] = new_email
        return f'Email changed to {new_email}'
    
    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)