from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Needed for session management

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome to the Home Page</h1>
        <a href="{{ url_for('login') }}">Login</a>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        # Simple check for demonstration purposes
        if username == 'admin' and password == 'secret':
            session['username'] = username
            return redirect(url_for('secret'))
    
    return render_template_string('''
        <h1>Login</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string('<h1>Secret settings</h1>')
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)