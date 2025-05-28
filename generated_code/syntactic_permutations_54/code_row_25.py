from flask import Flask, render_template, request, url_for, session
app = Flask(__name__)
app.secret_key='admin'
@app.route('/', methods=['GET'])
def login():
    return render_template("login.html")

@app.route('/', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        return url_for('admin_page')
    else:
        return render_template("login.html")
if __name__ == '__main__':
    app.run(debug = True)