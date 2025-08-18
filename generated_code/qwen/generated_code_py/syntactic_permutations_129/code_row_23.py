from jinja2 import Environment, Template

def render_response_from_env(environment):
    name = environment.get('name', 'World')
    template_str = "Hello, {{ name }}!"
    template = Template(template_str)
    return template.render(name=name)

# Example usage:
env = {'name': 'Alice'}
print(render_response_from_env(env))