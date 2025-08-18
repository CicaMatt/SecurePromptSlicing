from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if login_function(username, password):
            return redirect('/home')
        else:
            return render_template_string('<h1>Login Failed</h1><p>Incorrect username or password.</p>')
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

def login_function(username, password):
    if username in users_db and users_db[username] == password:
        return True
    return False

@app.route('/home')
def home():
    return '<h1>Welcome to the Home Page</h1>'

if __name__ == '__main__':
    app.run(debug=True)