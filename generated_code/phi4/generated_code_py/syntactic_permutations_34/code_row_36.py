from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database using a dictionary for demonstration purposes.
USER_DATABASE = {
    "user1": "password123",
    "admin": "adminpass"
}

LOGIN_PAGE_TEMPLATE = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form action="/login" method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
'''

@app.route('/')
def login():
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']

    if USER_DATABASE.get(username) == password:
        # Redirect to a new page, e.g., the user's dashboard
        return redirect(url_for('dashboard'))
    else:
        # Redirect back to login page with an error message (omitted here for simplicity)
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return "<h2>Welcome to your Dashboard!</h2>"

if __name__ == '__main__':
    app.run(debug=True)