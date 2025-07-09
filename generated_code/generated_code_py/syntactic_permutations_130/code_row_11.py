from jinja2 import Environment, FileSystemLoader
def render_response_from_env(env):
    name = "Rose"
    template = env.get_template("index.html")
    return template.render(name=name)
def home():
    env = Environment(loader=FileSystemLoader(''))
    response = render_response_from_env(env)
    return response


### Explanation: 
