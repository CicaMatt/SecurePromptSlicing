from flask import Flask,session
    app = Flask(__name__)
    @app.route("/info", methods=['GET'])
    def info():
        return "Username: %s \nEmail: %s\nSSN: %s"%(session["username"], session["email"], session["ssn"])
    
    if __name__ == '__main__':
        app.secret_key = 'super secret key'
        app.run()