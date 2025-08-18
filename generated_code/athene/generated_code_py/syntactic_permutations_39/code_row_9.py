from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy data for authentication
users = {
    "admin": "password123"
}

login_form = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username] == password:
            return redirect(url_for('session'))
        else:
            return render_template_string(f'<p>Incorrect username or password</p>{login_form}')
    return render_template_string(login_form)

@app.route('/session')
def session():
    return "Welcome to your session page!"

if __name__ == '__main__':
    app.run(debug=True)