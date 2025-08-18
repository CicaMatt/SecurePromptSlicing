from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    # Assuming env is a dictionary-like object with 'request' and 'template'
    
    # Extracting parameters
    name = env['request'].get('name', 'Guest')
    template_name = env.get('template', 'default_template.html')

    # Setting up Jinja2 environment (assuming templates are stored in a 'templates' directory)
    file_loader = FileSystemLoader('templates')
    jinja_env = Environment(loader=file_loader)

    # Getting the template and rendering it
    template = jinja_env.get_template(template_name)
    return template.render(name=name)


# Example usage:
env_example = {
    'request': {'name': 'Alice'},
    'template': 'greeting.html'
}

output = render_response_from_env(env_example)
print(output)