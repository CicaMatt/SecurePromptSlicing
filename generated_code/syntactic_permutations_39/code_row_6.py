import flask
        from flask_session import Session
        
        app = Flask(__name__)
        app.config["SESSION_PERMANENT"] = False
        app.config["SESSION_TYPE"] = "filesystem"
        Session(app)
        
        @app.route("/", methods=["GET", "POST"])
        def index():
            if flask.request.method == "POST":
                username = flask.request.form.get("username")
                password = flask.request.form.get("password")
                if username == "admin" and password == "password123":
                    session["user"] = username
                    return flask.redirect(flask.url_for("session"))
                else:
                    error = "Username or Password is incorrect."
                    return flask.render_template("index.html", error=error)
            return flask.render_template("index.html")
        
        @app.route("/session")
        def session():
            if "user" in session:
                username = session["user"]
                return f"Welcome {username}"
            return flask.redirect(flask.url_for("login"))