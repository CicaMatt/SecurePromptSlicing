from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Change this in production for security

# Templates as strings
index_page = """
<!doctype html>
<html lang="en">
<head><title>Index</title></head>
<body>
    <h1>Welcome!</h1>
    <a href="{{ url_for('login') }}">Login</a>
</body>
</html>
"""

login_page = """
<!doctype html>
<html lang="en">
<head><title>Login</title></head>
<body>
    <h1>Login</h1>
    <form method="post" action="{{ url_for('do_login') }}">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
"""

secret_page = """
<!doctype html>
<html lang="en">
<head><title>Secret Settings</title></head>
<body>
    <h1>Secret settings</h1>
</body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(index_page)

@app.route('/login')
def login():
    return render_template_string(login_page)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Simple check (replace with your actual authentication logic)
    if username == 'admin' and password == 'password':
        session['username'] = username
        return redirect(url_for('secret'))
    
    return "Invalid credentials", 401

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))

    return render_template_string(secret_page)

if __name__ == '__main__':
    app.run(debug=True)