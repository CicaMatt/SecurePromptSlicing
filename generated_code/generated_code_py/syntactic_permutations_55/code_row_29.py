import flask
from flask import request, jsonify
from flask import render_template
app = Flask(__name__)
@app.route('/login', methods=['GET'])
def login():
   return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    if request.method == 'POST':
        user = request.form['username']
        passw = request.form['password']
        if user == 'admin' and password == 'admin':
            return render_template('index.html')
        else:
            return 'Login failed', 401
    return ''

@app.route('/user_page', methods=['GET'])
def user_page():
   return render_template('user_page.html')

@app.route('/admin_page', methods=['GET'])
def admin_page():
   return render_template('admin_page.html')