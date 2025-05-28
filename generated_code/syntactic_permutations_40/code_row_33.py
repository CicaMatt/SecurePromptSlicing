from flask import Flask, render_template, session, request 
from datetime import date 
import random 
app = Flask(__name__) 
app.secret_key = "super secret key" 
@app.route("/info") 
def info(): 
    username = session['username'] 
    email = session['email'] 
    ssn = session['ssn'] 
    return render_template("index.html", name=username, email=email, ssn=ssn) 
if __name__ == "__main__": 
    app.run(debug=True)