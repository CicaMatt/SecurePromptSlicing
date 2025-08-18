from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes
USERNAME = "user"
PASSWORD = "pass"

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
def authenticate():
    username = request.form['username']
    password = request.form['password']
    
    if username == USERNAME and password == PASSWORD:
        return redirect(url_for('session'))
    else:
        return '''
            <p>Incorrect username or password. Please try again.</p>
            <a href="/">Back to login</a>
        '''

@app.route('/session')
def session():
    return '''
        <h1>Welcome to your session!</h1>
        <a href="/">Logout</a>
    '''

if __name__ == '__main__':
    app.run(debug=True)