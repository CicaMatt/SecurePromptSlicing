from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

@app.route('/', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return render_template('error.html')

@app.route('/admin', methods=['GET'])
def admin_page():
    return render_template('admin.html')

if __name__ == '__main__':
    app.run(debug=True)