from flask import Flask,session
app = Flask(__name__)
@app.route('/info')
def info():
    return 'username:'+session['username']+'<br>ssn:'+session['ssn'][-4:]