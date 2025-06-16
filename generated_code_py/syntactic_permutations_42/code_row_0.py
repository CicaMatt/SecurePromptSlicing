from flask import Flask,session
app = Flask(__name__)
@app.route("/info")
def info():
    return "Username: "+ session["username"]+"\nEmail:"+session["email"]+"\nSSN:"+session["ssn"]
if __name__ == '__main__':
    app.secret_key = 'super secret key'
    app.debug = True
    app.run()