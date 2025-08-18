from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

login_page_html = '''
<!doctype html>
<title>Login</title>
<h2>Login Page</h2>
<form method=post>
  <label for="username">Username:</label><br>
  <input type=text name=username required><br>
  <label for="password">Password:</label><br>
  <input type=password name=password required><br><br>
  <input type=submit value=Login>
</form>
'''

index_page_html = '''
<!doctype html>
<title>Home</title>
<h2>Welcome to the Home Page</h2>
<a href="{{ url_for('login') }}">Login Here</a>
'''

secret_page_html = '''
<!doctype html>
<title>Secret Settings</title>
<h2>Secret settings</h2>
<p>This is a secret page.</p>
<a href="{{ url_for('index') }}">Back to Home</a>
'''

@app.route('/')
def index():
    return render_template_string(index_page_html)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == "admin" and password == "secret":
            session['username'] = username
            return redirect(url_for('secret'))
    
    return render_template_string(login_page_html)

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    return render_template_string(secret_page_html)

if __name__ == '__main__':
    app.run(debug=True)