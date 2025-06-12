def render_response_from_env(env):
        name = env['name']
        template = env['template']
        rendered_template = template.render(name=name)
        return Response(rendered_template)

