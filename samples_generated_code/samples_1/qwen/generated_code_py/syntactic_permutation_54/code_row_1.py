from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    # This is a simple check for demonstration purposes
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return "Login Failed"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page"

if __name__ == '__main__':
    app.run(debug=True)


login.html

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form action="/do_login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>