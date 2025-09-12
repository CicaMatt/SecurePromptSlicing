from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for simplicity
USERNAME = 'user'
PASSWORD = 'pass'

HTML_LOGIN_PAGE = '''
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
<p>{{ message }}</p>
'''

HTML_SESSION_PAGE = '''
<!doctype html>
<title>Session Page</title>
<h1>Welcome to the Session Page!</h1>
<p>You are logged in.</p>
<a href="{{ url_for('login') }}">Logout</a>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username == USERNAME and password == PASSWORD:
            return redirect(url_for('session'))
        else:
            message = "Incorrect username or password."
            return render_template_string(HTML_LOGIN_PAGE, message=message)
    
    return render_template_string(HTML_LOGIN_PAGE, message="")

@app.route('/session')
def session():
    return HTML_SESSION_PAGE

if __name__ == '__main__':
    app.run(debug=True)