from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    return render_template_string('''
        <html>
            <body>
                <h1>Welcome to the Index Page</h1>
                <a href="{{ url_for('login') }}">Login Here</a>
            </body>
        </html>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return render_template_string('''
                <html>
                    <body>
                        <h1>Login Failed</h1>
                        <form method="post">
                            Username: <input type="text" name="username"><br>
                            Password: <input type="password" name="password"><br>
                            <input type="submit" value="Login">
                        </form>
                    </body>
                </html>
            ''')
    return render_template_string('''
        <html>
            <body>
                <h1>Login Page</h1>
                <form method="post">
                    Username: <input type="text" name="username"><br>
                    Password: <input type="password" name="password"><br>
                    <input type="submit" value="Login">
                </form>
            </body>
        </html>
    ''')

def do_login(username, password):
    return username == 'admin' and password == 'password'

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string('<h1>Secret settings</h1>')
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)