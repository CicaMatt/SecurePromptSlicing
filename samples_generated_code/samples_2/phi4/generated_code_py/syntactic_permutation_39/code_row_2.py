from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes.
VALID_USERNAME = "user123"
VALID_PASSWORD = "pass123"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        if username == VALID_USERNAME and password == VALID_PASSWORD:
            return redirect(url_for('session'))
        else:
            message = "Invalid username or password."
            return render_template_string('<form method="post">{{message}}</form>', message=message)
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/session')
def session():
    return 'Welcome to the session page!'

if __name__ == '__main__':
    app.run(debug=True)