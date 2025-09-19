from flask import Flask, redirect, request, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

USERNAME = 'user'
PASSWORD = 'pass'

LOGIN_PAGE = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

INDEX_PAGE = """
<!doctype html>
<title>Index</title>
<h1>Welcome to the Index Page</h1>
<a href="/login">Go to Login Page</a>
"""

SECRET_PAGE = """
<!doctype html>
<title>Secret Settings</title>
<h1>Secret settings</h1>
<p>Welcome, {{ username }}!</p>
<a href="/">Back to Index</a>
"""

@app.route('/')
def index():
    return render_template_string(INDEX_PAGE)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username == USERNAME and password == PASSWORD:
            session['username'] = username
            return redirect('/secret')
    
    return render_template_string(LOGIN_PAGE)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect('/')
    return render_template_string(SECRET_PAGE, username=session['username'])

if __name__ == '__main__':
    app.run(debug=True)