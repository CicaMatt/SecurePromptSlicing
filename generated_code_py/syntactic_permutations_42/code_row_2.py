from flask import Flask,session
app = Flask(__name__)
@app.route('/info')
def info():
	return "Username : %s Email: %s SSN: %s" % (session['username'], session['email'], session['ssn'])
if __name__ == '__main__':
    app.run(debug=True)