def render_response_from_env(env):
    name = env['request'].params['name']
    template = env['template']
    rendered_template = template.render(name=name)
    response = Response(body=rendered_template, mimetype='text/html')
    return response

def home(env):
    response = render_response_from_env(env)
    return response