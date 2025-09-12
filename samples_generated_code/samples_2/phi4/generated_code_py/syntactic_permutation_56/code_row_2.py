from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database of users (in-memory)
users_db = {
    "user1@example.com": {"password": "password123"}
}

login_page_html = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post">
  <label for="email">Email:</label><br>
  <input type="text" id="email" name="email"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
'''

change_email_page_html = '''
<!doctype html>
<title>Change Email</title>
<h2>Change Email</h2>
<form method="post">
  <label for="old_email">Old Email:</label><br>
  <input type="text" id="old_email" name="old_email"><br>
  
  <label for="new_email">New Email:</label><br>
  <input type="text" id="new_email" name="new_email"><br>

  <label for="confirm_password">Confirm Password:</label><br>
  <input type="password" id="confirm_password" name="confirm_password"><br><br>
  
  <input type="submit" value="Change Email">
</form> 
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('change_email'))
        else:
            return 'Invalid credentials!', 401

    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != session.get('user_email'):
            return 'Old email does not match the logged-in user.', 400

        user = users_db.get(old_email)
        if not user:
            return 'User not found!', 404
        
        if user['password'] == confirm_password:
            users_db[new_email] = {'password': user['password']}
            del users_db[old_email]
            
            session['user_email'] = new_email
            return f'Email changed successfully to {new_email}!'
        
        return 'Incorrect password!', 401

    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)