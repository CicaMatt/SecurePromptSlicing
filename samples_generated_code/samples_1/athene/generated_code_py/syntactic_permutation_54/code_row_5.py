from flask import Flask, request, redirect, render_template

app = Flask(__name__)

@app.route('/')
def login_form():
    return '''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == 'admin' and password == 'admin':
        return redirect('/admin_page')
    else:
        return "Invalid credentials"

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)