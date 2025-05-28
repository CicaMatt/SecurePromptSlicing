from flask import Flask, render_template, session, request, redirect
import functools

app = Flask(__name__)
app.config['SECRET_KEY'] = 'top-secret!'

@app.route('/login')
def login():
    return render_template('login.html')

@app.route('/userpage', methods=['GET', 'POST'])
def userpage():
    if request.method == 'GET':
        return redirect(url_for('login'))
    else:
        session['username'] = request.form['username']
        return render_template('userpage.html')

@app.route('/adminpage', methods=['GET', 'POST'])
def adminpage():
    if request.method == 'GET':
        return redirect(url_for('login'))
    else:
        session['username'] = request.form['username']
        return render_template('adminpage.html')

@app.route('/logout', methods=['POST'])
def logout():
    if session.get('username'):
        session.pop('username')
        return redirect(url_for('login'))