from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/')
def index():
    return '<a href="/login">Login</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'password123':
            return redirect(url_for('secret', username=username))
        else:
            return 'Invalid credentials'
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/secret')
def secret():
    return 'Secret settings'

if __name__ == '__main__':
    app.run(debug=True)