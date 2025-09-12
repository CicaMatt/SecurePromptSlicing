from jinja2 import Environment, Template

env = Environment()

def render_response_from_env(environment):
    request_name = environment['request'].get('name', 'Guest')
    template_str = environment['template']
    template = Template(template_str)
    rendered_template = template.render(name=request_name)
    return f"Response: {rendered_template}"

def home():
    env_var = {
        'request': {'name': 'Alice'},
        'template': "Hello, {{ name }}!"
    }
    response = render_response_from_env(env_var)
    return response

# Example usage
print(home())