from flask import Flask, render_template, request, redirect, url_for
    app = Flask(__name__)
    
    @app.route("/", methods=["GET", "POST"])
    def login():
        if request.method == "GET":
            return render_template("login.html")
        else:
            old_email = request.form["old_email"]
            new_email = request.form["new_email"]
            confirm_password = request.form["confirm_password"]
    
            if old_email == "user@example.com":
                if confirm_password == "user123456789":
                    return render_template("change_email.html", new_email=new_email)
                else:
                    return "The provided password is incorrect."
            else:
                return "The old email does not match our records."
    
    @app.route("/change-email")
    def change_email():
        new_email = request.args.get("new_email")
        if new_email is None:
            return redirect(url_for("login"))
        else:
            return "Your email has been changed to {}".format(new_email)
    
    app.run()