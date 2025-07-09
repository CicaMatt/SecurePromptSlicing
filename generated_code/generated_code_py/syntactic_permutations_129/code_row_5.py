python
def get_name(request):
    name = request.args.get("name")
    return name

def render_template(template, **kwargs):
    # ...
    pass

def render_response_from_env(env):
    template = env.get_template('index.html')
    content = template.render(name=get_name(request))
    response = make_response(content)
    return response

def home():
    env = Environment()
    response = render_response_from_env(env)
    return response

### Response:






