from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome to the Index Page</h1>
        <a href="{{ url_for('login') }}">Go to Login Page</a>
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
        <h1>Login Page</h1>
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
    
    return "<h1>Welcome to the Secret Page</h1><p>You are logged in as: {}</p>".format(session['username'])

if __name__ == '__main__':
    app.run(debug=True)