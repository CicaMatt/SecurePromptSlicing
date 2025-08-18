from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    form_html = '''
        <form method="post" action="/do_login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''
    return render_template_string(form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    # Simple check for admin
    if username == 'admin' and password == 'password':  # This should be replaced with a real authentication mechanism
        return redirect('/admin_page')
    else:
        return "Login failed"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)