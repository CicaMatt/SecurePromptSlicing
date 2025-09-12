from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Set a secret key for sessions

# HTML templates as strings for simplicity
index_html = '''
<!doctype html>
<html lang="en">
<head><title>Home</title></head>
<body>
    <h1>Welcome to the Home Page</h1>
    <a href="{{ url_for('login') }}">Login</a>
</body>
</html>
'''

login_html = '''
<!doctype html>
<html lang="en">
<head><title>Login</title></head>
<body>
    <h1>Login</h1>
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

secret_html = '''
<!doctype html>
<html lang="en">
<head><title>Secret Page</title></head>
<body>
    <h1>Secret settings</h1>
    <a href="{{ url_for('index') }}">Back to Home</a>
</body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(index_html)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Simple check for correct credentials
        if username == "admin" and password == "secret":
            session['username'] = username
            return redirect(url_for('secret'))
    
    return render_template_string(login_html)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    return render_template_string(secret_html)

if __name__ == '__main__':
    app.run(debug=True)