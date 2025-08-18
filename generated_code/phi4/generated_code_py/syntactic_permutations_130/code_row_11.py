from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    template_name = env['name']
    template = env.get_template(template_name)
    rendered_content = template.render()
    return f"Response: {rendered_content}"

def home():
    env = Environment(loader=FileSystemLoader('.'))
    response = render_response_from_env({'env': env, 'name': 'example.html'})
    return response

# Assuming there is a file named example.html in the current directory
print(home())