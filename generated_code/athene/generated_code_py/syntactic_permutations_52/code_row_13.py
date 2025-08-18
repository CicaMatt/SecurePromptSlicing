from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def check_credentials(username, password):
    return username == 'admin' and password == 'secret'

@app.route('/')
def do_login():
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']
    if check_credentials(username, password):
        return redirect(url_for('secret'))
    else:
        return 'Invalid credentials', 401

@app.route('/secret')
def secret():
    return "Secret settings"

if __name__ == '__main__':
    app.run(debug=True)