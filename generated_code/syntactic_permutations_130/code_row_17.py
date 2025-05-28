def render_response_from_env(env):
    template = env['template']
    return template.render(name=request.args.get('name'))