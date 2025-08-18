from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

login_form = '''
<form method="post" action="/do_login">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == 'admin' and password == 'admin':
        return redirect('/admin_page')
    else:
        return "Login Failed"

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page"

if __name__ == '__main__':
    app.run(debug=True)