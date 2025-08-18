from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Simulated database of users
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
            return redirect('/home')
        else:
            return redirect('/login?error=1')
    
    error = request.args.get('error')
    return render_template('login.html', error=error)

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/login.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    <form action="/login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    {% if error %}
        <p style="color:red;">Invalid username or password.</p>
    {% endif %}
</body>
</html>