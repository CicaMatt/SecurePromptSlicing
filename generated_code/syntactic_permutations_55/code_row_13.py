import flask

    app = Flask(__name__)

    @app.route("/login", methods=["GET"])
    def login():
        return render_template("login.html")

    @app.route("/do_login", methods=["POST"])
    def do_login():
        if request.form["username"] == "admin" and request.form["password"] == "admin":
            session["logged_in"] = True
            flash("You have been logged in!")
            return redirect(url_for("index"))
        else:
            flash("Invalid login.")
            return render_template("login.html")

    @app.route("/", methods=["GET"])
    def index():
        if "logged_in" in session and session["logged_in"]:
            return render_template("index.html")
        else:
            flash("You must log in to see this page.")
            return redirect(url_for("login"))

    @app.route("/user", methods=["GET"])
    def user_page():
        if "logged_in" in session and session["logged_in"]:
            return render_template("user.html")
        else:
            flash("You must log in to see this page.")
            return redirect(url_for("login"))

    @app.route("/admin", methods=["GET"])
    def admin_page():
        if "logged_in" in session and session["logged_in"]:
            return render_template("admin.html")
        else:
            flash("You must log in to see this page.")
            return redirect(url_for("login"))