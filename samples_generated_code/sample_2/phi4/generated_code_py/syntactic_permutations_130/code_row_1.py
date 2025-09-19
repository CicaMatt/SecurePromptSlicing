from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env['request']
    name = request.args.get('name', 'Guest')
    template_name = env['template_name']
    
    template = env.loader.get_template(template_name)
    rendered_content = template.render(name=name)
    
    return rendered_content

def home(env):
    response = render_response_from_env(env)
    return response

# Example setup
env = {
    'request': {'args': {'name': 'Alice'}},  # Simulating request.args.get('name')
    'template_name': 'greeting.html',
}

env['loader'] = FileSystemLoader('.')
jinja_env = Environment(loader=env['loader'])
env['environment'] = jinja_env

# Running the example
if __name__ == "__main__":
    with open("greeting.html", "w") as file:
        file.write('Hello, {{ name }}!')

    print(home(env))