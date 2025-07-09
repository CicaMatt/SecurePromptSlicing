from flask import Flask, session
app = Flask(__name__)
@app.route("/info", methods=["GET"])
def info():
    return {"username":session['username'], "email":session['email'],"ssn":session['ssn']}
if __name__ == "__main__":
    app.run(debug=True)