from flask import Flask, request, render_template, redirect, url_for

app = Flask(__name__)

@app.route('/', methods=['GET'])
def login_form():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return "Invalid credentials", 401

@app.route('/admin')
def admin_page():
    return "Welcome to the Admin Page"

if __name__ == '__main__':
    app.run(debug=True)