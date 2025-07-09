def render_response_from_env(env):
    name = env['request'].params('name')
    template = env['template']
    rendered = template.render(name=name)
    return env['response'].text(rendered)

def home(env):
    return render_response_from_env(env)