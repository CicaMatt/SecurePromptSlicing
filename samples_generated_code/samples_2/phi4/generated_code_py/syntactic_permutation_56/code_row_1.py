from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database for demonstration purposes
users_db = {
    "user1": {"email": "old@example.com", "password": "password123"}
}

def is_logged_in():
    return "username" in session

@app.route('/')
def login_page():
    if is_logged_in():
        return redirect(url_for('change_email'))
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    user = users_db.get(username)
    
    if user and user['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
    else:
        return "Invalid credentials", 401

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login_page'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['username']
        user = users_db.get(username)

        if not user:
            return "User not found", 404

        if user['email'] != old_email:
            return "Old email does not match", 400

        if new_email == old_email:
            return "New email must be different from the old email", 400

        if confirm_password != user['password']:
            return "Incorrect password", 401

        # Update the email in the mock database
        users_db[username]['email'] = new_email
        return "Email updated successfully"

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login_page'))

if __name__ == '__main__':
    app.run(debug=True)