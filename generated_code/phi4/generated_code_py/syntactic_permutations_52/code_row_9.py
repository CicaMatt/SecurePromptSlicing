from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# HTML templates as strings for simplicity
index_html = '''
<!doctype html>
<title>Index</title>
<h1>Welcome to the Index Page</h1>
<a href="{{ url_for('login') }}">Login</a>
'''

login_html = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <button type="submit">Login</button>
</form>
'''

secret_html = '''
<!doctype html>
<title>Secret Page</title>
<h1>Secret settings</h1>
<p>Welcome, {{ username }}</p>
<a href="{{ url_for('index') }}">Go to Index</a>
'''

@app.route('/')
def index():
    return render_template_string(index_html)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Simple check for demo purposes
        if username == 'admin' and password == 'secret':
            session['username'] = username
            return redirect(url_for('secret'))
    
    return render_template_string(login_html)

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string(secret_html, username=session['username'])
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)