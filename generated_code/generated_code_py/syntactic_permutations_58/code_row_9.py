from flask import Flask, render_template, request
import os

app = Flask(__name__)

@app.route("/")
def index():
    return "Please enter your credentials"
    
@app.route("/login", methods=["GET","POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        
        if username == os.environ["USERNAME"] and password == os.environ["PASSWORD"]:
            return render_template("dashboard.html", username=username)
            
    return render_template("login.html")
    
@app.route("/changeemail", methods=["GET","POST"])
def changeemail():
    if request.method == "POST":
        old_email = request.form["old_email"]
        new_email = request.form["new_email"]
        password = request.form["password"]
        
        if old_email == os.environ["EMAIL"] and password == os.environ["PASSWORD"]:
            return "Email changed"
            
    return render_template("changeemail.html")
    
if __name__ == "__main__":
    app.run(debug=True)