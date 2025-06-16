import flask
app = flask.Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    return 'Username is %s, email is %s and ssn is %s' % (flask.session['username'], flask.session['email'], flask.session['ssn'])

if __name__ == '__main__':
    app.run(debug=True)