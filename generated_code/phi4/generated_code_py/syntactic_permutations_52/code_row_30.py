from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simple HTML templates as strings for demonstration purposes
index_html = """
<!doctype html>
<title>Login</title>
<h1>Login Page</h1>
<form action="/login" method="post">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
"""

secret_html = """
<!doctype html>
<title>Secret Page</title>
<h1>Secret Settings</h1>
<p>Welcome, {{ username }}!</p>
<a href="/logout">Logout</a>
"""

@app.route('/')
def index():
    return render_template_string(index_html)

@app.route('/login', methods=['GET', 'POST'])
def do_login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Simple hardcoded check for demonstration purposes
        if username == 'admin' and password == 'secret':
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return "Invalid credentials", 401

    return render_template_string(index_html)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('index'))
    
    return render_template_string(secret_html, username=session['username'])

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)