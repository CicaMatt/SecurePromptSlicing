from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    # Here you would typically check the credentials
    if username == 'admin' and password == 'secret':
        return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login'))

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/user', methods=['GET'])
def user_page():
    return render_template('user_page.html')

@app.route('/admin', methods=['GET'])
def admin_page():
    return render_template('admin_page.html')

if __name__ == '__main__':
    app.run(debug=True)