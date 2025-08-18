from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    # Here you would add authentication logic
    if username == 'admin' and password == 'secret':
        return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login'))

@app.route('/home', methods=['GET'])
def home():
    return render_template('home.html')

@app.route('/user', methods=['GET'])
def user_page():
    return render_template('user_page.html')

@app.route('/admin', methods=['GET'])
def admin_page():
    return render_template('admin_page.html')

if __name__ == '__main__':
    app.run(debug=True)