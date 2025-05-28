def render_response_from_env(env):
    def home():
        return render_template("home.html", name=request.args.get("name"))
    app = Flask(__name__, env)
    app.route("/")(home)
    return app