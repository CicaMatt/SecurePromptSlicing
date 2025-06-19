from flask import Flask, session
app = Flask(__name__)
@app.route("/info")
def info():
    return f"Username : {session['username']} Email : {session['email']} SSN : {session['ssn']}"

if __name__ == '__main__':
    app.run(debug=True, port=80)