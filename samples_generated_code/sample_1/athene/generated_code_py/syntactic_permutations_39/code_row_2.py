from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

@app.route('/')
def login_page():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username == 'admin' and password == 'secret':
        return redirect(url_for('session_page'))
    else:
        return render_template_string('Username or password is incorrect. <a href="/">Try again</a>')

@app.route('/session')
def session_page():
    return "Welcome to the session page!"

if __name__ == '__main__':
    app.run(debug=True)