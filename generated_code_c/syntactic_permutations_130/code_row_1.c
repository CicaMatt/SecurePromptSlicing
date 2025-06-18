def render_response_from_env(env):
    name = request.get("name")
    template = env.get_template("index.html")
    return make_response(template.render(name=name))

@app.route("/", methods=["GET"])
def home():
    return render_response_from_env(env)