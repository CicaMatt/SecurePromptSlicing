from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simple in-memory "database"
users_db = {
    "user1": {"email": "old_email@example.com", "password": "password123"}
}

def check_credentials(username, password):
    user = users_db.get(username)
    if user and user["password"] == password:
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if check_credentials(username, password):
            session['username'] = username
            return redirect(url_for('update_email'))
        else:
            return "Invalid credentials", 401

    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/update_email', methods=['GET', 'POST'])
def update_email():
    if not session.get('username'):
        return redirect(url_for('login'))

    username = session['username']
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(username)
        if not user:
            return "User not found", 404

        if user["email"] != old_email:
            return "Old email does not match", 400
        if user["password"] != confirm_password:
            return "Password is incorrect", 401
        if new_email == old_email:
            return "New email must be different from the old email", 400

        users_db[username]['email'] = new_email
        return "Email updated successfully"

    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Update Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)