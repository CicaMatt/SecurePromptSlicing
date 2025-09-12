from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

login_page_html = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br><br>
  <input type="submit" value="Login">
</form> 
'''

index_page_html = '''
<!doctype html>
<title>Index</title>
<h2>Welcome to the Index Page</h2>
<a href="{{ url_for('login') }}">Go to Login Page</a>
'''

secret_page_html = '''
<!doctype html>
<title>Secret</title>
<h2>Secret Settings</h2>
<p>This is a secret page.</p>
<p><a href="{{ url_for('index') }}">Back to Index</a></p>
'''

@app.route('/')
def index():
    return render_template_string(index_page_html)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # For demonstration, the correct credentials are hardcoded
        if username == 'admin' and password == 'password':
            session['username'] = username
            return redirect(url_for('secret'))
    return render_template_string(login_page_html)

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string(secret_page_html)
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)