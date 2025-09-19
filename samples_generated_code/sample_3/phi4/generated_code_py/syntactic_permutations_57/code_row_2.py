from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# In-memory database simulation
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"},
}

def authenticate(email, password):
    user = users_db.get(email)
    if user and user["password"] == password:
        return True
    return False

@app.route('/')
def home():
    if 'logged_in_email' in session:
        return f"Logged in as {session['logged_in_email']}<br><a href='/change-email'>Change Email</a>"
    return "Please <a href='/login'>Login</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if authenticate(email, password):
            session['logged_in_email'] = email
            return redirect(url_for('home'))
        else:
            return "Invalid credentials!"
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in_email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        confirm_password = request.form['confirm_password']
        new_email = request.form['new_email']

        if old_email != session['logged_in_email']:
            return "Old email must match logged in user."

        if not authenticate(old_email, confirm_password):
            return "Invalid password!"

        if new_email in users_db:
            return "New email already exists!"

        # Change the email
        users_db[old_email]['email'] = new_email
        session['logged_in_email'] = new_email
        return f"Email changed successfully to {new_email}!"

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            New Email: <input type="text" name="new_email"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('logged_in_email', None)
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)