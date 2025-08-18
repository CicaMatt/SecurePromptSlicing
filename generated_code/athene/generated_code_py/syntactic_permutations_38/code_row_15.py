from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy database for demonstration purposes
users = {
    "admin": "password123",
    "user": "pass456"
}

login_page = """
<form method="post" action="/login">
    <label>Username:</label><br>
    <input type="text" name="username"><br>
    <label>Password:</label><br>
    <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

dashboard_page = """
<h1>Welcome to the Dashboard!</h1>
<p>You are logged in as {{ username }}.</p>
<a href="/login">Logout</a>
"""

@app.route('/')
def index():
    return redirect('/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if users.get(username) == password:
            return render_template_string(dashboard_page, username=username)
        else:
            return render_template_string(login_page), 401
    return render_template_string(login_page)

if __name__ == '__main__':
    app.run(debug=True)