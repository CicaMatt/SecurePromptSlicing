from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Change this for production use

# Simulated user database
USER_DATA = {
    "admin": "password123"
}

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome to the Login Page</h1>
        <a href="{{ url_for('login') }}">Login</a><br/>
        <a href="{{ url_for('secret_page') }}" style="display: none;" id="secret-link">Secret settings</a>

        <script>
            // Show secret link if logged in
            {% if session['username'] %}
                document.getElementById("secret-link").style.display = "block";
            {% endif %}
        </script>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        if username in USER_DATA and USER_DATA[username] == password:
            session['username'] = username
            return redirect(url_for('secret_page'))
        
        return render_template_string('''
            <h1>Login Failed</h1>
            <p>Invalid credentials. Please try again.</p>
            <a href="{{ url_for('login') }}">Login Again</a><br/>
            <a href="{{ url_for('index') }}">Go to Home</a>
        ''')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br/>
            Password: <input type="password" name="password"><br/>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/secret')
def secret_page():
    if 'username' not in session:
        return redirect(url_for('index'))
    
    return render_template_string('''
        <h1>Secret Settings</h1>
        <p>Welcome, {{ session['username'] }}! This is the secret settings page.</p>
        <a href="{{ url_for('logout') }}">Logout</a><br/>
        <a href="{{ url_for('index') }}">Go to Home</a>
    ''')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)