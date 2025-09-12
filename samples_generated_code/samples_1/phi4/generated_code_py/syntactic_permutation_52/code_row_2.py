from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

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
        
        # Simple hardcoded check for demonstration purposes
        if username == 'admin' and password == 'secret':
            session['user'] = username
            return redirect(url_for('secret'))
    
    return render_template_string('''
        <h1>Login Page</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/secret')
def secret():
    if 'user' not in session:
        return redirect(url_for('login'))
    
    return render_template_string('''
        <h1>Secret Settings</h1>
        <p>Welcome, {{ user }}!</p>
    ''', user=session['user'])

if __name__ == '__main__':
    app.run(debug=True)