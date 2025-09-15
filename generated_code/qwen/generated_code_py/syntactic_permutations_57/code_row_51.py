from flask import Flask, render_template, request, redirect, url_for, flash, session
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    "user1": {"old_email": "user1@example.com", "password_hash": generate_password_hash("securepassword")},
}

def generate_password_hash(password):
    # This is a placeholder function. In real applications, use werkzeug.security.generate_password_hash
    return password

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users_db.get(username)
        if user and check_password_hash(user['password_hash'], password):
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db[session['username']]
        
        if user['old_email'] != old_email:
            flash('Old email does not match')
        elif not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password')
        else:
            user['old_email'] = new_email
            flash('Email updated successfully')

    return render_template('change_email.html', current_email=users_db[session['username']]['old_email'])

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)








