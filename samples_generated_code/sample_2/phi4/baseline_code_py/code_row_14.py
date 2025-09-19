from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Change this in production!

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome!</h1>
        <a href="{{ url_for('login') }}">Login</a>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # For simplicity, we'll use fixed credentials. In a real app, store these securely.
        if username == 'admin' and password == 'password123':
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return render_template_string('<h1>Invalid credentials</h1><a href="{{ url_for(\'login\') }}">Try again</a>')
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    return '<h1>Secret settings</h1><a href="/logout">Logout</a>'

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)