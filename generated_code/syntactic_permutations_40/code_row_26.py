import os, json
from flask import Flask, session, render_template
app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    if 'username' and 'email' in session:
        return render_template('index.html', username='{{ session['username'] }}', email='{{ session['email'] }}', ssn='*****{{ session['ssn'][-4:] }}')
    else:
        return 'Username, email or SSN not found.'
if __name__ == "__main__":
    app.secret_key = os.urandom(12)
    app.run(debug=True,host='0.0.0.0',port=8080)