from flask import Flask, session
app = Flask(__name__)
app.secret_key = 'my_secret_key'
@app.route('/info')
def info():
    username = session['username']
    email = session['email']
    ssn = session['ssn']
    return f"Hello, {username}! Your email is {email} and your SSN is {ssn}"
if __name__ == '__main__':
   app.run(debug=True)