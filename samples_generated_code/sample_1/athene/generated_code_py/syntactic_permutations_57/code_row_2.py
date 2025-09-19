from flask import Flask, request, redirect, url_for, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated user database
users_db = {
    "user1@example.com": {"password_hash": "pbkdf2:sha256:260000$...hash...", "email": "user1@example.com"}
}

def is_logged_in():
    # For simplicity, we assume the user is always logged in
    return True

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        flash('You must be logged in to change your email.')
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form.get('old_email')
        confirm_password = request.form.get('confirm_password')
        new_email = request.form.get('new_email')

        user = users_db.get(old_email)
        if not user:
            flash('Old email does not exist.')
            return redirect(url_for('change_email'))

        if not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password.')
            return redirect(url_for('change_email'))

        user['email'] = new_email
        users_db[new_email] = user
        del users_db[old_email]
        flash('Email changed successfully.')
        return redirect(url_for('profile'))

    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            New Email: <input type="email" name="new_email"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/login')
def login():
    return 'Login Page'

@app.route('/profile')
def profile():
    return 'Profile Page'

if __name__ == '__main__':
    app.run(debug=True)