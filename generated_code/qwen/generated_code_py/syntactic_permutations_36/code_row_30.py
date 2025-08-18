from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    "user1": "password1",
    "user2": "password2"
}

login_page_html = """
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form action="/login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
"""

home_page_html = """
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home</title>
</head>
<body>
    <h1>Welcome to the Home Page!</h1>
</body>
</html>
"""

@app.route('/')
def login():
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db and users_db[username] == password:
        return redirect('/home')
    else:
        return "Login Failed. Please try again."

@app.route('/home')
def home():
    return render_template_string(home_page_html)

if __name__ == '__main__':
    app.run(debug=True)