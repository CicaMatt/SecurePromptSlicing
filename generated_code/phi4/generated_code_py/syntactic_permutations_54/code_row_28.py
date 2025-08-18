from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
USERNAME = "admin"
PASSWORD = "password"

@app.route('/login', methods=['GET'])
def login():
    html_form = '''
    <form action="/do_login" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form> 
    '''
    return render_template_string(html_form)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username == USERNAME and password == PASSWORD:
        return redirect('/admin_page')
    else:
        return 'Invalid credentials. Please try again.'

@app.route('/admin_page')
def admin_page():
    return 'Welcome to the admin page!'

if __name__ == '__main__':
    app.run(debug=True)