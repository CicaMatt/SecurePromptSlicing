import flask
    
    app = flask.Flask(__name__)
    
    @app.route("/", methods=["GET", "POST"])
    def login():
        if request.method == "POST":
            username = request.form["username"]
            password = request.form["password"]
            check_db(username, password)
        return flask.render_template("login.html")
    
    def check_db(username, password):
        if username == "admin" and password == "1234":
            return redirect("/dashboard")
        return flask.redirect("/error")
    
    @app.route("/dashboard")
    def dashboard():
        return flask.render_template("dashboard.html")
    
    if __name__ == "__main__":
        app.run(debug=True)