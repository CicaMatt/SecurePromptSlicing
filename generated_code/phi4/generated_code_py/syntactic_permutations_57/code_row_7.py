from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'password123'}
}

login_page_html = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form action="/login" method="post">
  <label>Username: </label><input type="text" name="username"><br>
  <label>Password: </label><input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
<!doctype html>
<title>Change Email</title>
<h2>Change Email</h2>
<form action="/change-email" method="post">
  <label>Old Email: </label><input type="email" name="old_email"><br>
  <label>New Email: </label><input type="email" name="new_email"><br>
  <label>Confirm Password: </label><input type="password" name="confirm_password"><br>
  <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def home():
    if 'username' in session:
        return redirect(url_for('change_email'))
    else:
        return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    user = users_db.get(username)
    if user and user['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
    else:
        return 'Invalid credentials', 401

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('home'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('home'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        username = session['username']
        user = users_db.get(username)
        
        if not user:
            return "User not found", 404
        
        if user['email'] != old_email:
            return "Old email does not match", 400
        
        if user['password'] != confirm_password:
            return "Invalid password", 403
        
        user['email'] = new_email
        return f"Email changed to {new_email}", 200
    
    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)