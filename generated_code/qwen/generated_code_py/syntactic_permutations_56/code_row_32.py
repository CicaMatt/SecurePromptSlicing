from flask import Flask, render_template, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users for demonstration purposes
users_db = {
    'user1': {'password': 'password123', 'email': 'old_email@example.com'}
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/change_email')
def change_email():
    if 'username' in session:
        return render_template('change_email.html', old_email=session['user_email'])
    else:
        flash('You need to log in first.')
        return redirect(url_for('login'))

@app.route('/submit_login', methods=['POST'])
def submit_login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db and users_db[username]['password'] == password:
        session['username'] = username
        session['user_email'] = users_db[username]['email']
        return redirect(url_for('change_email'))
    else:
        flash('Invalid credentials.')
        return redirect(url_for('login'))

@app.route('/submit_change_email', methods=['POST'])
def submit_change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']
    
    if 'username' in session:
        user_data = users_db[session['username']]
        
        if user_data['email'] == old_email and user_data['password'] == confirm_password:
            if new_email != old_email:
                user_data['email'] = new_email
                flash('Email updated successfully.')
                return redirect(url_for('change_email'))
            else:
                flash('New email must be different from the old email.')
        else:
            flash('Old email or password is incorrect.')
    else:
        flash('You need to log in first.')
    
    return redirect(url_for('change_email'))

@app.route('/logout')
def logout():
    session.pop('username', None)
    session.pop('user_email', None)
    flash('Logged out successfully.')
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)








