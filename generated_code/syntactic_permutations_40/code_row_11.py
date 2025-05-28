from flask import Flask, session
app = Flask(__name__)
@app.route('/')
def info():
    return 'Welcome, {session['username']}! Your email is {session['email']} and your SSN is XXXX-XXXX-XXXX-{session['ssn_4digits']}'
if __name__ == "__main__":
    app.secret_key = 'super secret key'
    session['username'] = 'John Doe'
    session['email'] = 'john@doe.com'
    session['ssn_4digits'] = '1234'
    app.run()