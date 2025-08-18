from flask import Flask, request, redirect, render_template

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        return redirect('/')
    else:
        return "Invalid credentials", 401

if __name__ == '__main__':
    app.run(debug=True)