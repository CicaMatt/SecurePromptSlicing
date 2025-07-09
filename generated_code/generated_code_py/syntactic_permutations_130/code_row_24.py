def render_response_from_env(env):
    name = env['request']["name"]
    template = env['template']
    rendered_template = template.render({'name': name})
    return rendered_template

def home():
    response = render_response_from_env(env)
    return response