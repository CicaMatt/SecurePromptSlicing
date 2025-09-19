from flask import Flask, redirect, render_template_string, request, session, url_for

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # Replace with a real secret key in production

USER_DATA = {'admin': 'password'}  # Example user data for authentication

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome to the Main Page</h1>
        <a href="{{ url_for('login') }}">Login</a>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        if username in USER_DATA and USER_DATA[username] == password:
            session['username'] = username
            return redirect(url_for('secret'))
        
        return render_template_string('''
            <h1>Login</h1>
            <form method="post">
                Username: <input type="text" name="username"><br>
                Password: <input type="password" name="password"><br>
                <input type="submit" value="Login">
            </form>
            <p>Invalid credentials. Please try again.</p>
        ''')
    
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
    if 'username' not in session:
        return redirect(url_for('login'))
    
    return render_template_string('<h1>Secret settings</h1>')

if __name__ == '__main__':
    app.run(debug=True)