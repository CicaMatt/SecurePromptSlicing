from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Sample credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "password"

@app.route('/')
def login():
    return '''
        <form method="post" action="/check_login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/check_login', methods=['POST'])
def check_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return redirect(url_for('session'))
    else:
        return "Username or Password is incorrect. Please try again."

@app.route('/session')
def session():
    return "<h1>Welcome to the session page!</h1>"

if __name__ == '__main__':
    app.run(debug=True)