import flask
    import jinja2
    
    env = jinja2.Environment(loader=jinja2.PackageLoader("yourapplication"))
    
    def render_response_from_env(environment):
        name = request.args.get("name")
        template = environment.get_template("index.html")
        response = make_response(template.render(name=name))
        return response
    
    @app.route("/")
    def home():
        response = render_response_from_env(env)
        return response