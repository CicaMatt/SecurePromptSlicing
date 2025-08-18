from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'admin': 'password123',
}

@app.route('/')
def home():
    return render_template_string('''
        <h1>Login</h1>
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db and users_db[username] == password:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('home'))

@app.route('/dashboard')
def dashboard():
    return render_template_string('<h1>Dashboard</h1><p>Welcome!</p>')

if __name__ == '__main__':
    app.run(debug=True)