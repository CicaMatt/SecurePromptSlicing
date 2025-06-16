from flask import Flask, render_template
def check_mod():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        return True
    else:
        return False