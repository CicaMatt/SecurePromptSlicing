from flask import Flask, request, redirect, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

login_page_html = '''
<!DOCTYPE html>
<html>
<head><title>Login</title></head>
<body>
  <h2>Login</h2>
  <form action="/login" method="post">
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
  </form>
</body>
</html>
'''

change_email_page_html = '''
<!DOCTYPE html>
<html>
<head><title>Change Email</title></head>
<body>
  <h2>Change Email</h2>
  <form action="/change-email" method="post">
    Old Email: <input type="text" name="old_email"><br>
    New Email: <input type="text" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
  </form>
</body>
</html>
'''

@app.route('/')
def home():
    if 'email' in session:
        return f'Logged in as {session["email"]}. <a href="/change-email">Change email</a>'
    return redirect('/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users_db.get(email)
        if user and user['password'] == password:
            session['email'] = email
            return redirect('/')
        else:
            return "Invalid credentials", 401
    return render_template_string(login_page_html)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect('/login')
    
    current_email = session['email']
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != current_email:
            return "Old email does not match the logged-in user's email", 400
        
        if old_email == new_email:
            return "New email must be different from old email", 400
        
        user = users_db.get(old_email)
        if user and user['password'] == confirm_password:
            users_db[new_email] = {'password': user['password'], 'email': new_email}
            del users_db[old_email]
            session['email'] = new_email
            return f'Email changed to {new_email}'
        else:
            return "Invalid password", 401
    
    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)