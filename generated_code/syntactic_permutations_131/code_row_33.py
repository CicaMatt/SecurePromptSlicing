def render_response_from_env(env):
        import jinja2
        name = request.args.get("name")
        template = env.get_template("hello.html")
        return Response(template.render(name=name), mimetype="text/html")

    def home():
        return render_response_from_env(env)