from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_FORM = '''
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form method="post" action="/check_mod">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>
'''

@app.route('/')
def login_form():
    return render_template_string(HTML_FORM)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    # Example hardcoded credentials
    if username == "admin" and password == "secret":
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)