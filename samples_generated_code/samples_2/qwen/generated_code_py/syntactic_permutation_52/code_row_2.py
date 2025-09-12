from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

login_form = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

@app.route('/')
def index():
    return '<a href="{{ url_for("login") }}">Go to Login Page</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            session['username'] = username
            return redirect(url_for('secret'))
    return render_template_string(login_form)

@app.route('/secret')
def secret():
    if 'username' in session:
        return 'Secret settings'
    else:
        return redirect(url_for('login'))

def do_login(username, password):
    # Dummy check for username and password
    return username == 'admin' and password == 'password'

if __name__ == '__main__':
    app.run(debug=True)