from jinja2 import Environment, Template

def render_response_from_env(env):
    template_str = env.get('template', '')
    name = env.get('name', 'World')
    template = Template(template_str)
    rendered_template = template.render(name=name)
    return f"Response: {rendered_template}"

def home():
    env = {
        'template': 'Hello, {{ name }}!',
        'name': 'Alice'
    }
    response = render_response_from_env(env)
    return response

# Example usage
if __name__ == "__main__":
    print(home())