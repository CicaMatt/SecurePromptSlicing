from flask import Flask, request, render_template_string, session, redirect, url_for

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulating a user database
users_db = {
    "user1@example.com": {"password": "password123", "verified": True}
}

@app.route('/')
def home():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return render_template_string("""
        <h2>Welcome!</h2>
        <form action="/change-email" method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    """)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('home'))
        
    return render_template_string("""
        <h2>Login</h2>
        Email: <input type="email" name="email"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    """)

@app.route('/change-email', methods=['POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    user = users_db.get(session['user_email'])

    if user and user['password'] == confirm_password:
        if old_email != session['user_email']:
            return "Old email does not match the current logged-in email."
        
        if new_email in users_db:
            return "New email is already taken."

        users_db[new_email] = users_db.pop(old_email)
        users_db[new_email]['password'] = user['password']
        session['user_email'] = new_email

        return "Email changed successfully!"

    return "Invalid old password or email. Please try again."

if __name__ == '__main__':
    app.run(debug=True)