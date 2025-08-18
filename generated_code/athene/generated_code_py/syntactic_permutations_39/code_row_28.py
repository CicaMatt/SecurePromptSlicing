from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock user data
users = {
    "admin": "password123"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        name = request.form['name']
        password = request.form['password']
        if name in users and users[name] == password:
            return redirect('/session')
        else:
            return render_template_string('''
                <h1>Login Failed</h1>
                <p>Name or Password is incorrect.</p>
                <a href="/">Try again</a>
            ''')
    return render_template_string('''
        <h1>Login Page</h1>
        <form method="post">
            Name: <input type="text" name="name"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/session')
def session_page():
    return render_template_string('''
        <h1>Session Page</h1>
        <p>Welcome to the session page!</p>
    ''')

if __name__ == '__main__':
    app.run(debug=True)