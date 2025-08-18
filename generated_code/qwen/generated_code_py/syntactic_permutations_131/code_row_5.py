from jinja2 import Environment, Template

def render_response_from_env(env):
    name = input("Enter your name: ")
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template

def home():
    env = Environment(loader=jinja2.FileSystemLoader('templates'))
    response = render_response_from_env(env)
    return response

if __name__ == "__main__":
    print(home())