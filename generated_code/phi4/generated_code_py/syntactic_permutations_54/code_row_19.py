from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# Simple in-memory storage for demonstration purposes.
USERS = {
    "admin": {"username": "admin", "password": "adminpass", "is_admin": True},
    "user": {"username": "user", "password": "userpass", "is_admin": False}
}

LOGIN_FORM = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post" action="/login">
  <label for="username">Username:</label>
  <input type="text" id="username" name="username"><br><br>
  <label for="password">Password:</label>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(LOGIN_FORM)

@app.route('/login', methods=['POST'])
def check_login():
    username = request.form['username']
    password = request.form['password']

    user = USERS.get(username)
    if user and user['password'] == password:
        if user['is_admin']:
            return redirect('/admin_page')
    return "Login Failed"

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)