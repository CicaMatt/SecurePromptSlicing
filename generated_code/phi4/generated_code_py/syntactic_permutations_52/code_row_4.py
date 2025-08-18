from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# HTML Templates as strings for simplicity
login_page_html = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post" action="/do_login">
    <label>Username: <input type="text" name="username"></label><br>
    <label>Password: <input type="password" name="password"></label><br>
    <input type="submit" value="Login">
</form>
'''

index_page_html = '''
<!doctype html>
<title>Index</title>
<h1>Welcome to the Index Page</h1>
<a href="/login">Go to Login Page</a>
'''

secret_page_html = '''
<!doctype html>
<title>Secret</title>
<h1>Secret settings</h1>
<p><a href="/">Back to Home</a></p>
'''

@app.route('/')
def index():
    return render_template_string(index_page_html)

@app.route('/login')
def login():
    return render_template_string(login_page_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    # Simple check for demonstration purposes
    if username == 'admin' and password == 'secret':
        session['username'] = username
        return redirect(url_for('secret'))
    else:
        return "Invalid credentials", 401

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string(secret_page_html)
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)