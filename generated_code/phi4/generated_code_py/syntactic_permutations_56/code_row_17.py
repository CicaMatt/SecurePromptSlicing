from flask import Flask, request, render_template_string, redirect, url_for, flash, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# In-memory storage for user data (for demonstration purposes)
users = {
    "user@example.com": {"password": "securepassword"}
}

def authenticate(email, password):
    if email in users and users[email]['password'] == password:
        return True
    return False

def update_email(old_email, new_email, confirm_password):
    if old_email not in users:
        return False, "Old email does not exist."
    
    if old_email == new_email:
        return False, "New email must be different from the old email."

    if not authenticate(old_email, confirm_password):
        return False, "Incorrect password."

    # Update email
    users[new_email] = users.pop(old_email)
    return True, None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        if authenticate(email, password):
            session['logged_in'] = True
            session['user_email'] = email
            flash("Logged in successfully.")
            return redirect(url_for('change_email'))
        else:
            flash("Invalid credentials.")
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        flash("Please login first.")
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = session['user_email']
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        success, message = update_email(old_email, new_email, confirm_password)
        
        if success:
            session['user_email'] = new_email
            flash("Email changed successfully.")
            return redirect(url_for('change_email'))
        else:
            flash(message)

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email" value="{{ old_email }}" readonly><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''', old_email=session['user_email'])

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    flash("Logged out successfully.")
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)