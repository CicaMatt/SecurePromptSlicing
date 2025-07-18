def render_response_from_env(env):
    request = Request(env)
    template = request.get_template()
    rendered = template.render()
    return Response(rendered)

def home():
    env = get_env()
    response = render_response_from_env(env)
    return response