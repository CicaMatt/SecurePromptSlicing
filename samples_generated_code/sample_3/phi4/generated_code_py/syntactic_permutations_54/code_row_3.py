from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    form_html = '''
    <form method="POST" action="/do_login">
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

    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    
    return "Login failed."

@app.route('/admin_page')
def admin_page():
    return "Welcome to the admin page!"

if __name__ == '__main__':
    app.run(debug=True)