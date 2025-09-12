from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    'user1': 'password123',
    'admin': 'adminpass'
}

@app.route('/')
def home():
    return '<h1>Welcome to the Home Page!</h1>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if users_db.get(username) == password:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login'))

    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- login.html -->
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Login</title>
</head>
<body>
  <h2>Login Page</h2>
  <form method="post" action="/login">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Login">
  </form>
</body>
</html>