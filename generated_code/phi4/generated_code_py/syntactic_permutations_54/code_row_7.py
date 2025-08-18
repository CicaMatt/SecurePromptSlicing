from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

HTML_FORM = '''
    <form method="post" action="/do_login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(HTML_FORM)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    # Dummy check for admin credentials
    if username == 'admin' and password == 'password':
        return redirect('/admin_page')
    
    return "Access Denied", 403

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)