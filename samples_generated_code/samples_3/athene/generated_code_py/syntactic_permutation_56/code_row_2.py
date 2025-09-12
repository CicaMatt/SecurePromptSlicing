from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

users = {
    'user1': {'email': 'user1@example.com', 'password': 'password1'}
}

def is_logged_in():
    return 'username' in session

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username]['password'] == password:
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            return "Invalid credentials"
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    username = session['username']
    user = users[username]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        
        if user['email'] != old_email:
            return "Old email does not match"
        if user['password'] != password:
            return "Incorrect password"
        if new_email == old_email:
            return "New email must be different from the old email"
        
        user['email'] = new_email
        return "Email updated successfully"
    
    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.secret_key = 'your_secret_key'
    app.run(debug=True)