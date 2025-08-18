from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulating a simple database with a dictionary
users_db = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

def authenticate(username, password):
    user = users_db.get(username)
    return user and user["password"] == password

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if authenticate(username, password):
            session['user'] = username
            return redirect(url_for('change_email'))
        else:
            return "Invalid credentials", 401

    return render_template_string('''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        username = session['user']
        user = users_db.get(username)

        if not (user and user["email"] == old_email and authenticate(username, password)):
            return "Invalid credentials or email", 401

        if old_email == new_email:
            return "New email must be different from the old email", 400

        user['email'] = new_email
        return "Email changed successfully"

    return render_template_string('''
    <form method="post">
        Old Email: <input type="text" name="old_email"><br>
        New Email: <input type="text" name="new_email"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Change Email">
    </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('user', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)