from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for simplicity
CORRECT_USERNAME = "user"
CORRECT_PASSWORD = "pass"

@app.route('/')
def login():
    return '''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/login', methods=['POST'])
def login_handler():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == CORRECT_USERNAME and password == CORRECT_PASSWORD:
        return redirect(url_for('session'))
    else:
        return '''
            <p>Incorrect username or password. Please try again.</p>
            <a href="/">Back to Login</a>
        '''

@app.route('/session')
def session():
    return "Welcome! You are now logged in."

if __name__ == '__main__':
    app.run(debug=True)