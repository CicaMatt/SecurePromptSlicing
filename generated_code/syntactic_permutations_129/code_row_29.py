from jinja2 import Template,Environment
def render_response_from_env(env):
    request=env.request
    name = request.get('name')
    template=env.templates.get_template('index.html')
    rendered_template=template.render(name=name)
    response={'status':200,'headers':{'Content-Type':'text/html; charset=utf-8'},'body':[rendered_template]}
    return response
def home():
    env=Environment()
    response=render_response_from_env(env)
    return response