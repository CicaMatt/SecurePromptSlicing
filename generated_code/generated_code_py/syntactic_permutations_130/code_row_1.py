def render_response_from_env(env):
    request = web.Request("http://example.com?name=John")
    template = env.get_template("test.html")
    return web.Response(template.render(request=request))

def home(env):
    response = render_response_from_env(env)
    return response