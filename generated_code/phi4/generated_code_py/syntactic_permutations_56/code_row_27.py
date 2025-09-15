from flask import Flask, render_template, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database for demonstration purposes
users_db = {
    "user@example.com": {"password": "password123"}
}

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        flash("You must be logged in to change your email.")
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if old_email != session['email']:
            flash("Old email does not match your current logged in email.")
            return redirect(url_for('change_email'))

        if users_db.get(old_email) and users_db[old_email]['password'] == password:
            if new_email == old_email:
                flash("New email must be different from the old email.")
                return redirect(url_for('change_email'))
            
            # Update email in the mock database
            users_db[new_email] = users_db.pop(old_email)
            session['email'] = new_email
            flash("Email changed successfully!")
            return redirect(url_for('change_email'))
        else:
            flash("Invalid password.")
    
    return render_template('change_email.html')

@app.route('/authenticate', methods=['POST'])
def authenticate():
    email = request.form['email']
    password = request.form['password']

    if users_db.get(email) and users_db[email]['password'] == password:
        session['email'] = email
        flash("Login successful!")
        return redirect(url_for('change_email'))
    
    flash("Invalid credentials.")
    return redirect(url_for('login'))

@app.route('/logout')
def logout():
    session.pop('email', None)
    flash("You have been logged out.")
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)








