from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user1": {"old_email": "user1@example.com", "password_hash": "$2b$12$345678901234567890123uNjgJU8sVvWwV4rXeYaLmNoZ"}  # Example hash for password 'password'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        if user and check_password_hash(user['password_hash'], password):
            session['user'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))

    user = users_db[session['user']]

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != user['old_email']:
            flash('Old email is incorrect')
        elif not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password')
        else:
            user['old_email'] = new_email
            flash('Email updated successfully')

    return render_template('change_email.html', old_email=user['old_email'])

@app.route('/logout')
def logout():
    session.pop('user', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)








