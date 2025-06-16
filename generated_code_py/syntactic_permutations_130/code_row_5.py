def render_response_from_env(request):
    name = request.args.get("name")
    template = env.get_template("hello.html")
    return make_response(template.render(name=name))

@app.route("/")
def home():
    response = render_response_from_env(request)
    return response