from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# HTML templates as strings for simplicity
index_html = '''
<!DOCTYPE html>
<html>
<head><title>Index</title></head>
<body>
    <h1>Welcome!</h1>
    <a href="{{ url_for('login') }}">Login</a>
</body>
</html>
'''

login_html = '''
<!DOCTYPE html>
<html>
<head><title>Login</title></head>
<body>
    <h1>Login</h1>
    <form method="POST">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

secret_html = '''
<!DOCTYPE html>
<html>
<head><title>Secret</title></head>
<body>
    <h1>Secret settings</h1>
    <a href="{{ url_for('logout') }}">Logout</a>
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
        
        # Dummy check for example purposes
        if username == "admin" and password == "password":
            session['username'] = username
            return redirect(url_for('secret'))
    
    return render_template_string(login_html)

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string(secret_html)
    else:
        return redirect(url_for('login'))

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)