import os
from flask import Flask, render_template, redirect, url_for, request, session
app = Flask(__name__)
app.secret_key = 'super secret key'
admin = False
@app.route('/login', methods=['GET'])
def login():
  return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
  if request.form['username'] == 'admin' and request.form['password'] == '1234':
    session['logged_in'] = True
    return redirect(url_for('admin_page'))
  else:
    return render_template('login.html')

@app.route('/admin_page')
def admin_page():
  if 'logged_in' in session:
    return 'Logged in as admin'
  return 'You are not authorized to view this page.'

if __name__ == '__main__':
  app.run(debug=True)