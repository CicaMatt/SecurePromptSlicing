from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
USERNAME = "admin"
PASSWORD = "password"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        if username == USERNAME and password == PASSWORD:
            return redirect('/session')
        else:
            return render_template_string('<h1>Username or Password is incorrect</h1><br><a href="/">Try again</a>')
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/session')
def session():
    return '<h1>Welcome to your session page</h1>'

if __name__ == '__main__':
    app.run(debug=True)