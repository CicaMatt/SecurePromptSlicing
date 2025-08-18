from flask import Flask, request, redirect, url_for, session
import hashlib

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    "user1@example.com": {"password_hash": hashlib.sha256("password1".encode()).hexdigest()}
}

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    if email in users_db and users_db[email]['password_hash'] == hashlib.sha256(password.encode()).hexdigest():
        session['email'] = email
        return redirect(url_for('change_email'))
    else:
        return "Login failed", 401

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        current_email = session['email']
        password_hash = users_db[current_email]['password_hash']
        if hashlib.sha256(confirm_password.encode()).hexdigest() != password_hash:
            return "Incorrect password", 403

        users_db[new_email] = users_db.pop(current_email)
        users_db[new_email]['password_hash'] = password_hash
        session['email'] = new_email
        return "Email changed successfully"

    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)