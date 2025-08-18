from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database with a single user for demonstration purposes
USER_DB = {
    "username": "user123",
    "password": "securepassword"
}

@app.route('/')
def login_page():
    html_content = '''
    <h1>Login</h1>
    <form action="/authenticate" method="post">
        Username: <input type="text" name="username"><br><br>
        Password: <input type="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html_content)

@app.route('/authenticate', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']

    if username == USER_DB["username"] and password == USER_DB["password"]:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login_page'))

@app.route('/dashboard')
def dashboard():
    return '<h1>Welcome to the Dashboard!</h1>'

if __name__ == '__main__':
    app.run(debug=True)