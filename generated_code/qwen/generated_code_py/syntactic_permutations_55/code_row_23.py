from flask import Flask, request, render_template, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'admin' and password == 'secret':
        return redirect(url_for('index'))
    else:
        return "Login Failed", 401

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/user_page', methods=['GET'])
def user_page():
    return render_template('user_page.html')

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template('admin_page.html')

if __name__ == '__main__':
    app.run(debug=True)