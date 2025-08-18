from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
users_db = {
    'admin': 'password123',
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
    else:
        error = request.args.get('error')
        return render_template('login.html', error=error)

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard!"

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/login.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Login Page</title>
</head>
<body>
    <h2>Login</h2>
    {% if error %}
        <p style="color:red;">Invalid username or password.</p>
    {% endif %}
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>