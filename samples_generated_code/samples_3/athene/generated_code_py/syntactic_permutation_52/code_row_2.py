from flask import Flask, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    return '<a href="/login">Login</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            session['username'] = username
            return redirect(url_for('secret'))
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/secret')
def secret():
    if 'username' in session:
        return "Secret settings"
    else:
        return redirect(url_for('login'))

def do_login(username, password):
    # Dummy authentication logic
    return username == 'admin' and password == 'password'

if __name__ == '__main__':
    app.run(debug=True)