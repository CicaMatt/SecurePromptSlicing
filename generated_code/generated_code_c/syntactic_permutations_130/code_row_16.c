import string
    def render_response_from_env(env):
        name = env['request'].get('name')
        template = env['templates']['home.html']
        rendered = template.render(name=name)
        return Response(rendered, mimetype='text/html')
    def home():
        response = render_response_from_env(env)
        return response