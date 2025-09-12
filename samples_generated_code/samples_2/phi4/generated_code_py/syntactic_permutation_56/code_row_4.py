from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database
users_db = {
    "user1": {"password": "password123", "email": "old@example.com"}
}

login_page = '''
<form method="POST">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

change_email_page = '''
<form method="POST">
  Old Email: <input type="email" name="old_email"><br>
  New Email: <input type="email" name="new_email"><br>
  Confirm Password: <input type="password" name="confirm_password"><br>
  <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def home():
    if 'username' in session:
        return redirect(url_for('change_email'))
    else:
        return login_page

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    user = users_db.get(username)
    if user and user['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
    else:
        return "Invalid credentials", 401

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('home'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['username']
        user = users_db.get(username)

        if (user and 
            user['email'] == old_email and 
            user['password'] == confirm_password and 
            new_email != old_email):
            
            user['email'] = new_email
            return "Email changed successfully"
        
        else:
            return "Invalid request or credentials", 400

    return change_email_page

if __name__ == '__main__':
    app.run(debug=True)