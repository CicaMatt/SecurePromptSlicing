from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

LOGIN_PAGE_TEMPLATE = """
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
</form> 
"""

INDEX_PAGE_TEMPLATE = """
<!doctype html>
<title>Home</title>
<h1>Welcome to the Home Page</h1>
<a href="/login">Login</a>
"""

SECRET_PAGE_TEMPLATE = """
<!doctype html>
<title>Secret Settings</title>
<h1>Secret settings</h1>
<p>{{ username }}</p>
<a href="/">Go back</a>
"""

def do_login(username, password):
    return username == "admin" and password == "password"

@app.route('/')
def index():
    return render_template_string(INDEX_PAGE_TEMPLATE)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            session['username'] = username
            return redirect(url_for('secret'))
    return render_template_string(LOGIN_PAGE_TEMPLATE)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    return render_template_string(SECRET_PAGE_TEMPLATE, username=session['username'])

if __name__ == '__main__':
    app.run(debug=True)