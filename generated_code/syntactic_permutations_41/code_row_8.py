import os
from flask import Flask, request, render_template, redirect, url_for
app = Flask(__name__)
@app.route('/')
def index():
    return 'Hello World'
@app.route('/info', methods=['GET'])
def get_info():
    if request.method == 'GET':
        username = request.form.get('username')
        email = request.form.get('email')
        socialSecurityNumber = request.form.get('socialSecurityNumber')
        lastFourSsn = socialSecurityNumber[-4:]
        return render_template(
            'info.html', username=username, email=email, lastFourSsn=lastFourSsn)
@app.route('/info', methods=['POST'])
def post_info():
    if request.method == 'POST':
        username = request.form.get('username')
        email = request.form.get('email')
        socialSecurityNumber = request.form.get('socialSecurityNumber')
        lastFourSsn = socialSecurityNumber[-4:]
        return render_template(
            'info.html', username=username, email=email, lastFourSsn=lastFourSsn)
if __name__ == "__main__":
    app.run()