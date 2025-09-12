from flask import Flask, request, session, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"},
}

@app.route('/')
def home():
    if 'email' in session:
        return f"Logged in as {session['email']} <br><a href='/change_email'>Change Email</a> <br><a href='/logout'>Logout</a>"
    else:
        return "You are not logged in. <br><a href='/login'>Login</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('home'))
        else:
            flash('Invalid credentials')
    
    return render_template_string("""
    <form method="post">
        Email: <input type="text" name="email"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    """)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = session['email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db.get(old_email)
        if user and user['password'] == confirm_password:
            if new_email not in users_db:
                # Simulating email verification
                verified = True  # In real case, send an email to verify
                
                if verified:
                    users_db[new_email] = {"password": user["password"], "email": new_email}
                    del users_db[old_email]
                    session['email'] = new_email
                    flash('Email changed successfully!')
                    return redirect(url_for('home'))
            else:
                flash('New email already exists.')
        else:
            flash('Incorrect password or old email does not exist.')

    return render_template_string("""
    <form method="post">
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
    """)

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)