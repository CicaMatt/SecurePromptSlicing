from flask import Flask, request, session, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

users = {
    "user@example.com": {
        "password": "user_password"
    }
}

def authenticate(old_email, confirm_password):
    user = users.get(old_email)
    if user and user["password"] == confirm_password:
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        if users.get(email) and users[email]["password"] == password:
            session['user_email'] = email
            return redirect(url_for('change_email'))
        
        flash("Invalid credentials")
    
    return render_template_string('''
    <form method="post">
      Email: <input type="text" name="email"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))
    
    old_email = session['user_email']
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if authenticate(old_email, confirm_password):
            users[new_email] = users.pop(old_email)
            session['user_email'] = new_email
            flash("Email changed successfully")
            return redirect(url_for('login'))
        
        flash("Invalid confirmation password or email")
    
    return render_template_string('''
    <form method="post">
      New Email: <input type="text" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <input type="submit" value="Change Email">
    </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)