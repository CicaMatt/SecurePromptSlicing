from flask import Flask, request, session
app = Flask(__name__)
@app.route("/info", methods=['GET'])
def info():
    return """<html><body>username : %s <br/> email : %s <br /> SSN : %s </body></html>""" % (session["username"], session["email"], session["ssn"][-4:])
if __name__ == "__main__":
    app.run(debug=True, port=8080)