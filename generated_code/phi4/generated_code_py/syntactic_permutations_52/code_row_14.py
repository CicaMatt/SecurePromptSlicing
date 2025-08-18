from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# HTML templates
index_page = '''
<!doctype html>
<html lang="en">
<head><title>Index</title></head>
<body>
    <h1>Welcome to the Index Page</h1>
    <a href="{{ url_for('login') }}">Login</a>
</body>
</html>
'''

login_page = '''
<!doctype html>
<html lang="en">
<head><title>Login</title></head>
<body>
    <h1>Login</h1>
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

secret_page = '''
<!doctype html>
<html lang="en">
<head><title>Secret</title></head>
<body>
    <h1>Secret settings</h1>
</body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(index_page)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Simple hardcoded check for demonstration purposes
        if username == "admin" and password == "secret":
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return "Invalid credentials", 401

    return render_template_string(login_page)

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string(secret_page)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)