from flask import Flask, render_template, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user1": {"email": "old_email1@example.com", "password": "password1"},
    "user2": {"email": "old_email2@example.com", "password": "password2"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        if user and user['password'] == password:
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))

    username = session['username']
    user = users_db[username]

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if user['email'] != old_email:
            flash('Old email does not match')
        elif user['password'] != confirm_password:
            flash('Incorrect password')
        else:
            user['email'] = new_email
            flash('Email updated successfully')
            return redirect(url_for('login'))

    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)








