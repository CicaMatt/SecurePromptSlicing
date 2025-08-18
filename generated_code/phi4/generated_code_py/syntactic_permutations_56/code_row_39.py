from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy user database
users_db = {
    "user@example.com": {"password": "password123"}
}

login_page_html = '''
<!doctype html>
<title>Login</title>
<h2>Login</h2>
<form method="post" action="/login">
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
<form method="post" action="/change-email">
  <label for="old_email">Old Email:</label><br>
  <input type="text" id="old_email" name="old_email"><br>
  <label for="new_email">New Email:</label><br>
  <input type="text" id="new_email" name="new_email"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Change Email">
</form> 
'''

@app.route('/')
def index():
    if 'email' in session:
        return redirect(url_for('change_email'))
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    user = users_db.get(email)
    if user and user['password'] == password:
        session['email'] = email
        return redirect(url_for('change_email'))
        
    return "Invalid credentials", 401

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('index'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('index'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if old_email != session['email']:
            return "Old email does not match the current session", 400

        user = users_db.get(old_email)
        if user and user['password'] == password:
            if new_email in users_db:
                return "New email already exists", 409
            
            users_db[new_email] = users_db.pop(old_email)
            session['email'] = new_email
            return redirect(url_for('change_email'))
        
        return "Invalid password", 401

    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)