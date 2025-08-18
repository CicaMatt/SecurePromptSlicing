from flask import Flask, request, redirect, url_for

app = Flask(__name__)

users = {
    "admin": "password123",
    "user1": "pass456"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username] == password:
            return redirect(url_for('session_page'))
        else:
            return "Username or password is incorrect"
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/session')
def session_page():
    return "Welcome to the session page!"

if __name__ == '__main__':
    app.run(debug=True)