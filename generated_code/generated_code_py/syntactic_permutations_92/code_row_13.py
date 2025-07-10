from flask import Flask, render_template, request, redirect, url_for, flash
import bcrypt

app = Flask(__name__)
app.secret_key = "mysecret"

@app.route("/", methods=["GET","POST"])
def index():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        
        # Hashing the password with bcrypt library
        hashed_password = bcrypt.hashpw(password, bcrypt.gensalt())
        flash("Registration successful!")
        return redirect(url_for('index'))
    
    return render_template("index.html")

if __name__ == "__main__":
   app.run(debug=True)