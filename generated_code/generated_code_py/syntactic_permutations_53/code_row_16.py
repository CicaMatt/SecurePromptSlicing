from flask import Flask, redirect, url_for
import json
app = Flask(__name__)
@app.route('/')
def index():
    return redirect(url_for('login'))
@app.route('/user')
def user():
    return redirect(url_for('login'))
@app.route('/admin')
def admin():
    if not isAdmin:
        return redirect(url_for('login'))
    else:
        return redirect(url_for('adminpage'))
if __name__ == '__main__':
    app.run()