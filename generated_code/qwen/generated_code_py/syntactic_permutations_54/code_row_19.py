from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login_form():
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    # Example check for admin credentials
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return "Login failed. Please try again."

@app.route('/admin_page')
def admin_page():
    return "<h1>Welcome to the Admin Page</h1>"

if __name__ == '__main__':
    app.run(debug=True)