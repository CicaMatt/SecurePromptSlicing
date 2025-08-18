from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes
USERNAME = 'admin'
PASSWORD = 'password123'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == USERNAME and password == PASSWORD:
            return redirect('/session')
        else:
            return render_template_string('''
                <h1>Login Failed</h1>
                <p>Incorrect username or password.</p>
                <a href="/">Try again</a>
            ''')
    return render_template_string('''
        <h1>Login Page</h1>
        <form method="post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password"><br><br>
            <button type="submit">Login</button>
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