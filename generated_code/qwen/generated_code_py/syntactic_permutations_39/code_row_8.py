from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = 'admin'
VALID_PASSWORD = 'password'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == VALID_USERNAME and password == VALID_PASSWORD:
            return redirect('/session')
        else:
            return render_template_string('''
                <h1>Login Failed</h1>
                <p>Incorrect username or password. Please try again.</p>
                <a href="/">Go Back to Login</a>
            ''')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br><br>
            Password: <input type="password" name="password"><br><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/session')
def session():
    return render_template_string('<h1>Welcome to the Session Page</h1>')

if __name__ == '__main__':
    app.run(debug=True)