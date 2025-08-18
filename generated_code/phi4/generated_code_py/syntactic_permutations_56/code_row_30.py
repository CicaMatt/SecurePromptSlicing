from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

login_page_html = '''
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form action="/login" method="post">
  <label for="email">Email:</label>
  <input type="text" id="email" name="email"><br><br>
  <label for="password">Password:</label>
  <input type="password" id="password" name="password"><br><br>
  <button type="submit">Login</button>
</form>
'''

change_email_page_html = '''
<!doctype html>
<title>Change Email</title>
<h1>Change Your Email</h1>
<form action="/change-email" method="post">
  <label for="old_email">Old Email:</label>
  <input type="text" id="old_email" name="old_email"><br><br>
  
  <label for="new_email">New Email:</label>
  <input type="text" id="new_email" name="new_email"><br><br>

  <label for="password">Password:</label>
  <input type="password" id="password" name="password"><br><br>
  
  <button type="submit">Change Email</button>
</form>
'''

@app.route('/')
def index():
    if 'email' in session:
        return f'Logged in as {session["email"]}. <a href="/change-email">Change Email</a> | <a href="/logout">Logout</a>'
    else:
        return '<a href="/login">Login</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('index'))
    
    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        current_user = users_db.get(session['email'])

        if current_user and current_user['password'] == password:
            if old_email == session['email'] and old_email != new_email:
                users_db[new_email] = {"password": current_user["password"], "email": new_email}
                del users_db[old_email]
                session['email'] = new_email
                return redirect(url_for('index'))
        
    return render_template_string(change_email_page_html)

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)