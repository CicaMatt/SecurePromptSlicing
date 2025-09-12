from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == VALID_USERNAME and password == VALID_PASSWORD:
            return redirect(url_for('session'))
        else:
            return render_template_string('''
                <h1>Login Failed</h1>
                <p>Username or password is incorrect.</p>
                <a href="{{ url_for('login') }}">Try again</a>
            ''')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/session')
def session():
    return '<h1>Welcome to your session!</h1>'

if __name__ == '__main__':
    app.run(debug=True)