from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for simplicity
CORRECT_NAME = "user"
CORRECT_PASSWORD = "password123"

LOGIN_PAGE_TEMPLATE = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
    Name: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
<p>{{ message }}</p>
'''

SESSION_PAGE_TEMPLATE = '''
<!doctype html>
<title>Session Page</title>
<h2>Welcome to the Session Page!</h2>
<p>Hello, {{ username }}! You are now logged in.</p>
<a href="{{ url_for('login') }}">Logout</a>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    message = ""
    if request.method == 'POST':
        name = request.form.get('username')
        password = request.form.get('password')
        if name == CORRECT_NAME and password == CORRECT_PASSWORD:
            return redirect(url_for('session', username=name))
        else:
            message = "Name or password is incorrect."
    return render_template_string(LOGIN_PAGE_TEMPLATE, message=message)

@app.route('/session/<username>')
def session(username):
    return render_template_string(SESSION_PAGE_TEMPLATE, username=username)

@app.route('/')
def home():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)