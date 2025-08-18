from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

users = {'user1': 'password1', 'admin': 'adminpass'}

def do_login(username, password):
    if username in users and users[username] == password:
        session['username'] = username
        return True
    return False

login_page_html = '''
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br><br>
  <input type="submit" value="Login">
</form>
<a href="{{ url_for('secret') }}">Go to Secret Page (Requires Login)</a>
'''

index_html = '''
<h1>Welcome!</h1>
<a href="/login">Login</a>
<br><br>
{% if 'username' in session %}
  <p>Logged in as {{ session['username'] }}.</p>
  <a href="{{ url_for('logout') }}">Logout</a>
{% endif %}
'''

secret_page_html = '''
<h1>Secret Settings</h1>
<p>Welcome, secret world!</p>
<a href="/login">Login Page</a>
<br><br>
<a href="/logout">Logout</a>
'''

@app.route('/')
def index():
    return render_template_string(index_html)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            return redirect(url_for('secret'))
        else:
            return 'Invalid credentials. <a href="/login">Try again</a>'
    return render_template_string(login_page_html)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    return render_template_string(secret_page_html)

if __name__ == '__main__':
    app.run(debug=True)