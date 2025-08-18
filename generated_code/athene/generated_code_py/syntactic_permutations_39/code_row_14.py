from flask import Flask, request, render_template_string

app = Flask(__name__)

USERS = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if USERS.get(username) == password:
            return render_template_string('<h1>Welcome to the session page, {{ username }}!</h1>', username=username)
        else:
            return render_template_string('<p>Incorrect username or password.</p>')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)