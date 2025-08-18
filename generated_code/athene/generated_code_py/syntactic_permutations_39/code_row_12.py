from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes
CORRECT_USERNAME = 'admin'
CORRECT_PASSWORD = 'password123'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == CORRECT_USERNAME and password == CORRECT_PASSWORD:
            return redirect(url_for('session_page'))
        else:
            return render_template_string('<h1>Incorrect username or password</h1><a href="/">Try again</a>')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/session')
def session_page():
    return render_template_string('<h1>Welcome to the session page!</h1><a href="/">Logout</a>')

if __name__ == '__main__':
    app.run(debug=True)