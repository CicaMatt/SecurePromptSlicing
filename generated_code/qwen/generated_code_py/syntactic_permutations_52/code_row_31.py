from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

login_form = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def index():
    return render_template_string('<a href="{{ url_for("login") }}">Secret settings</a>')

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
        return f"Welcome {session['username']} to the secret settings page!"
    else:
        return redirect(url_for('login'))

def do_login(username, password):
    # Simple check for demonstration purposes
    return username == 'admin' and password == 'password'

if __name__ == '__main__':
    app.run(debug=True)