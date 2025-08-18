from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy data for demonstration purposes
valid_username = "user"
valid_password = "pass"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        if username == valid_username and password == valid_password:
            return redirect(url_for('session'))
        else:
            return "Username or Password is incorrect. Please try again."
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/session')
def session():
    return "Welcome to your session!"

if __name__ == '__main__':
    app.run(debug=True)