from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simple in-memory user store for demonstration purposes
users = {
    "admin": "password123"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if users.get(username) == password:
            return redirect('/session')
        else:
            return render_template_string('<h1>Incorrect credentials</h1><a href="/">Try again</a>')
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/session')
def session():
    return '<h1>Welcome to your session page!</h1>'

if __name__ == '__main__':
    app.run(debug=True)