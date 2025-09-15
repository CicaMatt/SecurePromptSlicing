from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# In-memory user database simulation
users_db = {
    "user1@example.com": {"password": generate_password_hash("securepassword123")},
}

@app.route('/')
def index():
    if 'email' in session:
        return render_template('index.html', email=session['email'])
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and check_password_hash(user['password'], password):
            session['email'] = email
            return redirect(url_for('index'))
        else:
            flash('Invalid email or password')
    return render_template('login.html')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        flash('You need to be logged in to change your email.')
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db.get(old_email)
        if not user:
            flash('Old email does not exist.')
        elif not check_password_hash(user['password'], confirm_password):
            flash('Incorrect password.')
        else:
            # Change email
            users_db[new_email] = users_db.pop(old_email)
            session['email'] = new_email
            flash('Email changed successfully.')
            return redirect(url_for('index'))
    
    return render_template('change_email.html')

if __name__ == '__main__':
    app.run(debug=True)












