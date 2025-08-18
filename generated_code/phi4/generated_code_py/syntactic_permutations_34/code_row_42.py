from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# Simulated database as a dictionary for demonstration purposes
DATABASE = {
    'user1': 'password123',
    'admin': 'adminpass'
}

LOGIN_PAGE = '''
<!doctype html>
<html lang="en">
  <head><title>Login Page</title></head>
  <body>
    <h2>Login</h2>
    <form method="POST" action="/login">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
  </body>
</html>
'''

DASHBOARD_PAGE = '''
<!doctype html>
<html lang="en">
  <head><title>Dashboard Page</title></head>
  <body>
    <h2>Welcome to the Dashboard!</h2>
    <p>You are logged in.</p>
    <a href="/logout">Logout</a>
  </body>
</html>
'''

@app.route('/')
def login():
    return render_template_string(LOGIN_PAGE)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']

    if username in DATABASE and DATABASE[username] == password:
        return redirect(url_for('dashboard'))
    
    return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    # For security purposes, a real application should check authentication here
    return render_template_string(DASHBOARD_PAGE)

@app.route('/logout')
def logout():
    # In a real app, you would clear session data or tokens here
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)