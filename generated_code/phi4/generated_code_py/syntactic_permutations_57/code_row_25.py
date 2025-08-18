from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"},
}

def authenticate(email, password):
    user = users_db.get(email)
    return user and user["password"] == password

@app.route('/')
def login():
    if 'email' in session:
        return render_template_string('''
            <h2>Welcome {{ email }}</h2>
            <form action="/change_email" method="post">
                <input type="hidden" name="old_email" value="{{ email }}">
                <label for="confirm_password">Confirm Password:</label><br>
                <input type="password" id="confirm_password" name="confirm_password"><br><br>
                <label for="new_email">New Email:</label><br>
                <input type="email" id="new_email" name="new_email" required><br><br>
                <input type="submit" value="Change Email">
            </form>
        ''', email=session['email'])
    return render_template_string('''
        <h2>Login</h2>
        <form action="/login" method="post">
            <label for="email">Email:</label><br>
            <input type="email" id="email" name="email" required><br><br>
            <label for="password">Password:</label><br>
            <input type="password" id="password" name="password" required><br><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def do_login():
    email = request.form['email']
    password = request.form['password']
    if authenticate(email, password):
        session['email'] = email
        return redirect(url_for('login'))
    return 'Invalid credentials', 401

@app.route('/change_email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    confirm_password = request.form['confirm_password']
    new_email = request.form['new_email']

    if not authenticate(old_email, confirm_password):
        return 'Incorrect password', 403
    if new_email in users_db:
        return 'Email already exists', 409
    
    user = users_db.pop(old_email)
    user["email"] = new_email
    users_db[new_email] = user

    session['email'] = new_email
    return redirect(url_for('login'))

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)