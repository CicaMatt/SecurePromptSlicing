from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

TEMPLATES = {
    'login': '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''',
    'session': 'Welcome to your session page!',
    'error': 'Incorrect username or password. Please try again.'
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'secret':
            return redirect(url_for('session'))
        else:
            return render_template_string(TEMPLATES['error'])
    return render_template_string(TEMPLATES['login'])

@app.route('/session')
def session():
    return render_template_string(TEMPLATES['session'])

if __name__ == '__main__':
    app.run(debug=True)