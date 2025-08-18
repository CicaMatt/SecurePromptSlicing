from flask import Flask, request, redirect, render_template_string, session

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
    return '<a href="/login">Go to Login Page</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            session['username'] = username
            return redirect('/secret')
    return render_template_string(login_form)

@app.route('/secret')
def secret():
    if 'username' in session:
        return "Secret settings"
    else:
        return redirect('/login')

def do_login(username, password):
    # For demonstration purposes, let's assume the correct credentials are:
    correct_username = 'admin'
    correct_password = 'password123'
    return username == correct_username and password == correct_password

if __name__ == '__main__':
    app.run(debug=True)