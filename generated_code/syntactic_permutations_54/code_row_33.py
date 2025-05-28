from flask import Flask, redirect, render_template, url_for, request

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    user = request.form['username']
    passw = request.form['password']
    if user == 'admin' and passw == '1234':
        return redirect(url_for('admin_page'))
    else:
        return

@app.route('/admin')
def admin_page():
    return "Welcome to the admin page!"

if __name__ == '__main__':
    app.run()