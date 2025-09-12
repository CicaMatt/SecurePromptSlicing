from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy data for demonstration purposes
VALID_USERNAME = "admin"
VALID_PASSWORD = "password"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        if username == VALID_USERNAME and password == VALID_PASSWORD:
            return redirect(url_for('session'))
        else:
            return render_template('login.html', error='Invalid username or password')
    return render_template('login.html')

@app.route('/session')
def session():
    return "Welcome to your session page!"

if __name__ == '__main__':
    app.run(debug=True)


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>
    {% if error %}
        <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post" action="/">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>