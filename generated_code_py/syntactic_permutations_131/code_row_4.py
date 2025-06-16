def home(env):
    name = get_name_param(env)
    tpl = env.get_template("index.html")
    rendered_tpl = tpl.render(name=name)
    return render_response_from_env(env, rendered_tpl)
def render_response_from_env(env, rendered_tpl):
    response = Response()
    response.body = rendered_tpl.encode("utf-8")
    return response
def get_name_param(env):
    params = env["params"]
    name = params["name"]
    return name