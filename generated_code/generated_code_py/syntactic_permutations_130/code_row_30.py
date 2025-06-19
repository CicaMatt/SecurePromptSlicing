def home(env):
    return render_response_from_env(env)

def render_response_from_env(env):
    name = env['request'].params.get('name')
    template = env['template']
    body = template.render(name=name)
    return Response(body=body)