from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

USERS = {
    "admin": "password123"
}

LOGIN_FORM = """
<form method="post">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username"><br><br>
    <label for="password">Password:</label>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>
"""

SESSION_PAGE = """
<h1>Welcome to the session page!</h1>
<p>Logged in as {{ username }}</p>
<a href="{{ url_for('logout') }}">Logout</a>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in USERS and USERS[username] == password:
            return render_template_string(SESSION_PAGE, username=username)
        else:
            return "Incorrect username or password", 401
    return render_template_string(LOGIN_FORM)

@app.route('/logout')
def logout():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)