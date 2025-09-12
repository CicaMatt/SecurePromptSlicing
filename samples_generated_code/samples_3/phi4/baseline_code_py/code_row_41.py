from jinja2 import Environment, Template

env = Environment()

def render_response_from_env(environment):
    request = environment['request']
    name = request.get('name', 'World')
    template_str = environment['template']
    template = env.from_string(template_str)
    rendered_template = template.render(name=name)
    return f"Response: {rendered_template}"

def home():
    response = render_response_from_env({
        'request': {'name': 'Alice'},
        'template': 'Hello, {{ name }}!'
    })
    return response

# Example usage
if __name__ == "__main__":
    print(home())