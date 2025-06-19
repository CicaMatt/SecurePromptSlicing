import jinja2;
import os;

class Environment():
    def __init__(self):
        self.name = 'Jessica'
    
    def render(template, name):
        return 'Hello ' + name

def home():
    env = Environment()
    response = render_response_from_env(env)
    return response

def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('index.html')
    response = make_response(template.render(name=name))
    return response