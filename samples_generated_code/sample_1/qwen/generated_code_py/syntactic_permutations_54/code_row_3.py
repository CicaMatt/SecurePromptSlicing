from flask import Flask, render_template, request, redirect

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        return redirect('/admin_page')
    else:
        return 'Login failed'

@app.route('/admin_page')
def admin_page():
    return 'Welcome to the Admin Page'

if __name__ == '__main__':
    app.run(debug=True)




