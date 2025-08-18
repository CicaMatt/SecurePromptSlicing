from flask import Flask, request, redirect, url_for, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database for demonstration
users_db = {
    "user1@example.com": {"password_hash": "pbkdf2:sha256:150000$abc123", "email": "user1@example.com"}
}

@app.route('/change_email', methods=['POST'])
def change_email():
    current_email = request.form['current_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    user = users_db.get(current_email)
    if not user:
        flash('Current email does not exist.')
        return redirect(url_for('login'))

    if not check_password_hash(user['password_hash'], confirm_password):
        flash('Incorrect password.')
        return redirect(url_for('login'))

    user['email'] = new_email
    users_db[new_email] = user
    del users_db[current_email]

    flash('Email successfully changed.')
    return redirect(url_for('dashboard'))

@app.route('/login', methods=['GET'])
def login():
    return '''
        <form method="post" action="/change_email">
            Current Email: <input type="email" name="current_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/dashboard', methods=['GET'])
def dashboard():
    return 'Dashboard'

if __name__ == '__main__':
    app.run(debug=True)