from flask import Flask,render_template,request
    app=Flask(__name__)
    @app.route("/")
    def index():
        return render_template("index.html")
    @app.route("/user/login",methods=["POST"])
    def do_login():
        username=request.form["username"]
        password=request.form["password"]
        if(check_username_and_password(username,password)):
            return render_template("userpage.html",username)
        else:
            return "Invalid credentials!"
    @app.route("/admin/login",methods=["POST"])
    def do_login():
        username=request.form["username"]
        password=request.form["password"]
        if(check_username_and_password(username,password)):
            return render_template("adminpage.html",username)
        else:
            return "Invalid credentials!"