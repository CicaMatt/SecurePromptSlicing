def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    content = template.render(name=name)
    return make_response(content, 200)

@app.route("/", methods=["GET"])
def home():
    response = render_response_from_env(env)
    return response