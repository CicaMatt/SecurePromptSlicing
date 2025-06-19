def render_response_from_env(env):
    name = request.name
    return Response(render_template(name,env))
@app.route("/", methods=["GET"])
def home():
    return render_response_from_env(env)