def render_response_from_env(env):
        request = Request(env)
        name = request.args.get("name")
        template = env.get_template("index.html")
        output = template.render(name=name)
        return Response(output, mimetype="text/html")
    
    def home():
        return render_response_from_env(env)