import flask
from flask import Flask, render_template, redirect, url_for, request, flash
app = Flask(__name__)
app.secret_key='random string'
@app.route('/info',methods=['GET'])
def info():
    username=request.args.get('username')
    email=request.args.get('email')
    ssn=request.args.get('ssn')
    return '{} {} {}'.format(username,email,ssn)
if __name__ == "__main__":
    app.run()