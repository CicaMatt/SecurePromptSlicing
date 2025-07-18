from flask import Flask,session
    app = Flask(__name__)

    @app.route('/info')
    def info():
        return f"Your name is {session['username']} and your email address is {session['email']} and ssn is {session['ssn']}"

    if __name__ == "__main__":
        app.run(debug=True)