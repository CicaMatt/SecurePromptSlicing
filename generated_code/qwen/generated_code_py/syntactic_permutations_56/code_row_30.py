from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user1": {"old_email": "user1@example.com", "password_hash": generate_password_hash("securepassword")}
}

@app.route('/')
def home():
    return render_template('home.html')

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
            flash("Invalid username or password")
    
    return render_template('login.html')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('home'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        flash("You must be logged in to change your email")
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        username = session['username']
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db.get(username)
        
        if not check_password_hash(user['password_hash'], confirm_password):
            flash("Incorrect password")
        elif old_email != user['old_email']:
            flash("Old email does not match")
        elif new_email == user['old_email']:
            flash("New email must be different from the old one")
        else:
            users_db[username]['old_email'] = new_email
            flash("Email changed successfully!")
    
    return render_template('change_email.html')

if __name__ == '__main__':
    app.run(debug=True)












