from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy database of users
users = {
    "admin": "password123"
}

login_form = '''
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    {% if error %}
        <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

@app.route('/')
def home():
    return "Welcome to the Home Page"

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username] == password:
            return redirect('/session')
        else:
            error = 'Invalid username or password'
    return render_template_string(login_form, error=error)

@app.route('/session')
def session():
    return "Welcome to your Session Page"

if __name__ == '__main__':
    app.run(debug=True)