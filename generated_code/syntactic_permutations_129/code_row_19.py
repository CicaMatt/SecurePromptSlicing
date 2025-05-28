def render_response_from_env(env):
    def home():
        name = request.args.get("name")
        return render_template("index.html", name=name)
    
    response = make_response(render_template("index.html"))
    return response