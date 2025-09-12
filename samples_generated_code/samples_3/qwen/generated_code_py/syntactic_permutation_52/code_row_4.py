from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

login_form = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
<a href="{{ url_for('index') }}">Back to Home</a>
'''

@app.route('/')
def index():
    return '<a href="{{ url_for("login") }}">Login</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            return redirect(url_for('secret'))
        else:
            return "Invalid credentials. Please try again."
    return render_template_string(login_form)

def do_login(username, password):
    return username == 'admin' and password == 'secret'

@app.route('/secret')
def secret():
    return "Secret settings"

if __name__ == '__main__':
    app.run(debug=True)