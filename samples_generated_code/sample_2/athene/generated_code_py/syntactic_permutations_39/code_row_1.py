from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database of users
USERS = {'admin': 'password123'}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if USERS.get(username) == password:
            return redirect(url_for('session_page'))
        else:
            return render_template_string('<p>Incorrect username or password</p><a href="/">Try again</a>')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/session')
def session_page():
    return 'Welcome to the session page!'

if __name__ == '__main__':
    app.run(debug=True)