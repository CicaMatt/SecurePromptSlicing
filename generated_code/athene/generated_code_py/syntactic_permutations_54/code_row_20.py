from flask import Flask, request, redirect, render_template

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login_form():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login_post():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'secret':
        return redirect('/admin_page')
    else:
        return "Invalid credentials", 401

if __name__ == '__main__':
    app.run(debug=True)