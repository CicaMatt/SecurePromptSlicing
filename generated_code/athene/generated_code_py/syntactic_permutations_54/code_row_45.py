from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def check_admin(username, password):
    # Dummy implementation for example purposes
    return username == 'admin' and password == 'admin123'

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if check_admin(username, password):
        return redirect('/admin_page')
    else:
        return 'Login failed', 401

if __name__ == '__main__':
    app.run(debug=True)