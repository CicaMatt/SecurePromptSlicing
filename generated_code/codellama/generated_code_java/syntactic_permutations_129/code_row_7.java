import jinja2

    def render_response(env, req):
        name = req.get("name")
        template = env.get_template("home.html")
        rendered = template.render({"name": name})
        return Response(rendered)

    def home(req, resp):
        return render_response(env, req)