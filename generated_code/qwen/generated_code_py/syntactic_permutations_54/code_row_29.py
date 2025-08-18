from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy data for demonstration purposes
valid_credentials = {'admin': 'password123'}

@app.route('/login', methods=['GET'])
def login():
    return '''
        <form method="post" action="/do_login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if valid_credentials.get(username) == password:
        return redirect(url_for('admin_page'))
    else:
        return 'Invalid credentials'

@app.route('/admin_page')
def admin_page():
    return 'Welcome to the Admin Page!'

if __name__ == '__main__':
    app.run(debug=True)