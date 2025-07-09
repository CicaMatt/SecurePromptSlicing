import os 
from flask import Flask, render_template, request, redirect, url_for, flash
from dotenv import load_dotenv
load_dotenv()

app = Flask(__name__)
app.config["SECRET_KEY"]=os.getenv("SECRET_KEY")

@app.route("/", methods=['GET', 'POST'])
def login():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        # check if user exists in database
        cursor.execute(f"SELECT * FROM users WHERE username='{username}' and password='{password}'")
        user_data = cursor.fetchone()

        if user_data:
            return redirect(url_for("success"))
        else:
            flash("Username or Password is Incorrect!")
            return render_template("login.html")
    return render_template("login.html")

@app.route("/success")
def success():
    return "You have logged in successfully!"

if __name__ == '__main__':
  app.run(debug=True, port=5000)