from flask import Flask, render_template, request, redirect
app = Flask(__name__)

def login(username, password):
    #query database for username
    
    if username == "admin" and password == "password":
        return True
    else:
        return False
@app.route("/login", methods=["GET","POST"])
def login_page():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        if login(username, password):
            return redirect("home")
        else:
            return render_template("login.html", message="Invalid credentials")
    return render_template("login.html")

if __name__ == "__main__":
    app.run()