from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
users_db = {
    'admin': 'password123'
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if users_db.get(username) == password:
            return f"Welcome, {username}!"
        else:
            return redirect('/')
    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)


# login.html
'''
<!DOCTYPE html>
<html>
<head>
    <title>Login Page</title>
</head>
<body>
    <form method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>
'''