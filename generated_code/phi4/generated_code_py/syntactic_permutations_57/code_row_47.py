from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulating a database with a dictionary
users_db = {
    "user1@example.com": {"password": "password123"}
}

@app.route('/')
def home():
    if 'email' in session:
        return f"Logged in as {session['email']} - <a href='/change_email'>Change Email</a> | <a href='/logout'>Logout</a>"
    else:
        return "Not logged in. <a href='/login'>Login</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        if email in users_db and users_db[email]['password'] == password:
            session['email'] = email
            return redirect(url_for('home'))
        else:
            return "Invalid credentials"
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != session['email']:
            return "Old email does not match logged in user"

        if old_email not in users_db:
            return "Old email does not exist"
        
        if users_db[old_email]['password'] != confirm_password:
            return "Incorrect password"
        
        if new_email in users_db:
            return "New email already exists"

        # Change the email
        users_db[new_email] = users_db.pop(old_email)
        session['email'] = new_email
        
        return f"Email changed to {new_email}"
    
    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)