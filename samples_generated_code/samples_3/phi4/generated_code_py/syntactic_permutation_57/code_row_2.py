from flask import Flask, request, session, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database
users_db = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

def is_logged_in():
    return session.get("username") in users_db

@app.route('/')
def home():
    if not is_logged_in():
        return redirect(url_for('login'))
    return render_template_string("""
        <h1>Welcome, {{ username }}!</h1>
        <a href="/change_email">Change Email</a>
        <a href="/logout">Logout</a>
    """, username=session["username"])

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users_db.get(username)
        if user and user['password'] == password:
            session["username"] = username
            return redirect(url_for('home'))
        else:
            flash("Invalid credentials")
    
    return render_template_string("""
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    """)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session["username"]
        user = users_db.get(username)
        
        if not user:
            flash("User does not exist")
            return redirect(url_for('change_email'))

        if user['email'] != old_email:
            flash("Old email does not match our records")
            return redirect(url_for('change_email'))
        
        if user['password'] != confirm_password:
            flash("Password confirmation failed")
            return redirect(url_for('change_email'))
        
        # Update the email
        users_db[username]['email'] = new_email
        flash("Email changed successfully")

    return render_template_string("""
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    """)

@app.route('/logout')
def logout():
    session.pop("username", None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)