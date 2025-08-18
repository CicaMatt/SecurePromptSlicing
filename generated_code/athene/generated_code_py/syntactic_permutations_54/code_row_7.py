from flask import Flask, request, redirect, render_template

app = Flask(__name__)

@app.route('/', methods=['GET'])
def login_form():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        return redirect('/admin_page')
    else:
        return "Login Failed", 401

if __name__ == '__main__':
    app.run(debug=True)