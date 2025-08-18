from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy data to simulate a database
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['user_email'] = email
            return redirect(url_for('change_email'))
    
    return render_template_string("""
    <form method="post">
      Email: <input type="text" name="email"><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
    """)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = session['user_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        
        if user and user['password'] == confirm_password:
            if new_email in users_db:
                return "New email already exists."
            
            # Update the email
            del users_db[old_email]
            users_db[new_email] = {"password": user['password'], "email": new_email}
            session['user_email'] = new_email
            
            return "Email changed successfully!"

        return "Invalid password or email."

    return render_template_string("""
    <form method="post">
      New Email: <input type="text" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br><br>
      <input type="submit" value="Change Email">
    </form>
    """)

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)