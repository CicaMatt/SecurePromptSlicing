def render_response_from_env(env):
        request = env['request']
        name = request.params.get("name")
        template = env['loader'].get_template("index.html")
        rendered = template.render(name=name)
        return Response(body=rendered, content_type="text/html")

