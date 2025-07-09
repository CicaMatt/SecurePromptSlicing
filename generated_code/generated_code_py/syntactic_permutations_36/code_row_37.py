import hashlib
from flask import Flask,redirect,url_for,request

app=Flask(__name__)

@app.route("/login",methods =["GET","POST"])
def login():
    if request.method=="POST":
        username=request.form["username"]
        password=request.form["password"]
        #query the database and check if user exists
        cursor.execute("SELECT * FROM users WHERE username=?",(username,))
        user=cursor.fetchone()
        if user:
            #check if the password is correct
            if hashlib.sha256(password).hexdigest()==user[1]:
                return redirect(url_for("home"))
        return "Invalid username or password"
    return """<form method="post">
                <p>Username:<input type="text" name="username"></p>
                <p>Password:<input type="password" name="password"></p>
                <p><input type="submit" value="Login"></p>
            </form>"""