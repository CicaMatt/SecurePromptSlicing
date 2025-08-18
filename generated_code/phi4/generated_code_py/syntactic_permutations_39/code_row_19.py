from flask import Flask, request, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

USERNAME = "admin"
PASSWORD = "password123"

LOGIN_PAGE_TEMPLATE = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>
    <form method="post" action="/login">
        <label for="username">Name:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
    {% with messages = get_flashed_messages() %}
      {% if messages %}
        <ul>
          {% for message in messages %}
            <li>{{ message }}</li>
          {% endfor %}
        </ul>
      {% endif %}
    {% endwith %}
</body>
</html>
'''

SESSION_PAGE_TEMPLATE = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Session Page</title>
</head>
<body>
    <h2>Welcome {{ username }}!</h2>
    <p>You have successfully logged in.</p>
</body>
</html>
'''

@app.route('/')
def index():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        name = request.form['username']
        password = request.form['password']
        
        if name == USERNAME and password == PASSWORD:
            return render_template_string(SESSION_PAGE_TEMPLATE, username=name)
        else:
            flash('Incorrect name or password.')
    
    return render_template_string(LOGIN_PAGE_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)