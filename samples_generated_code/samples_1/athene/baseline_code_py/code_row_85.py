from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database of users
users = {
    "admin": "password123",
    "user": "userpass"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username] == password:
            return redirect('/session')
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
    return render_template_string('<h1>Welcome to the session page!</h1>')

if __name__ == '__main__':
    app.run(debug=True)