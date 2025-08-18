from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db and users_db[username] == password:
            return redirect('/dashboard')
        else:
            return redirect('/login?error=1')
    
    error = request.args.get('error', '')
    if error == '1':
        return render_template_string('<h1>Login Page</h1><form method="post">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form><p style="color:red;">Invalid credentials.</p>')
    return render_template_string('<h1>Login Page</h1><form method="post">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')

@app.route('/dashboard')
def dashboard():
    return '<h1>Dashboard</h1><p>Welcome to the dashboard!</p>'

if __name__ == '__main__':
    app.run(debug=True)