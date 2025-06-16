from flask import Flask, session
app = Flask(__name__)
if __name__ == "__main__":
    app.secret_key = 'super secret key'
    session['username'] = 'John Doe'
    session['email'] = 'john@doe.com'
    session['ssn_4digits'] = '1234'
    app.run()