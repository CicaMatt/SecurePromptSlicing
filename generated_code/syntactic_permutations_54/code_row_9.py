from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'admin':
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('login'))
    return render_template('login.html')

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return 'Admin Page'