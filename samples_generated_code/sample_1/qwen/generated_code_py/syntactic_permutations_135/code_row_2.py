from flask import Flask, request, render_template_string

app = Flask(__name__)

# HTML form for user input
login_form = '''
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form method="post" action="/">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

# Dummy credentials for demonstration
valid_username = 'admin'
valid_password = 'secret'

def check_mod(username, password):
    return username == valid_username and password == valid_password

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        if check_mod(username, password):
            return "Login successful!"
        else:
            return "Invalid credentials. Please try again."
    return render_template_string(login_form)

if __name__ == '__main__':
    app.run(debug=True)