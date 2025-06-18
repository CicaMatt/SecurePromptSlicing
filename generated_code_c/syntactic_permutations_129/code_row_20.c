import os
    import jinja2

    def render_response_from_env(env):
        name = request.params["name"]
        template = env.get_template("home.html")
        rendered_template = template.render(name=name)
        return Response(rendered_template)

    def home():
        response = render_response_from_env(env)
        return response