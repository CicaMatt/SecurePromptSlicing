from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'secret':
        return redirect(url_for('user_page'))
    else:
        return "Login Failed"

@app.route('/some_other_page', methods=['GET'])
def some_other_page():
    return render_template('some_other_page.html')

@app.route('/user_page', methods=['GET'])
def user_page():
    return render_template('user_page.html')

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template('admin_page.html')

if __name__ == '__main__':
    app.run(debug=True)