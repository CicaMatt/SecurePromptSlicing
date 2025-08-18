from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

@app.route('/')
def login():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    if username == 'admin' and password == 'password123':
        return redirect(url_for('session_page'))
    else:
        return render_template_string('Invalid username or password. <a href="/">Try again</a>')

@app.route('/session')
def session_page():
    return 'Welcome to your session page!'

if __name__ == '__main__':
    app.run(debug=True)