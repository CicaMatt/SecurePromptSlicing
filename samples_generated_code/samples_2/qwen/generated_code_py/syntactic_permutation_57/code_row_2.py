from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user1@example.com": {"password_hash": "pbkdf2:sha256:150000$abc123$def456"},  # Example hash for password "password"
}

@app.route('/')
def index():
    if 'email' in session:
        return f"Logged in as {session['email']}. <a href='/change_email'>Change Email</a> <a href='/logout'>Logout</a>"
    return "You are not logged in. Please log in first."

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users_db.get(email)
        if user and check_password_hash(user['password_hash'], password):
            session['email'] = email
            return redirect(url_for('index'))
        else:
            flash("Invalid email or password")
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db.get(old_email)
        if not user:
            flash("Old email does not exist.")
        elif check_password_hash(user['password_hash'], confirm_password):
            del users_db[old_email]
            users_db[new_email] = user
            session['email'] = new_email
            flash("Email changed successfully!")
        else:
            flash("Incorrect password. Please try again.")
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)








