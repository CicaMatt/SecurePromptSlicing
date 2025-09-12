from jinja2 import Environment, BaseLoader

def render_response_from_env(env):
    request = {'name': 'World'}  # Simulating a request object for demonstration
    name = request.get('name', '')
    template = env.from_string('Hello, {{ name }}!')
    rendered_template = template.render(name=name)
    return rendered_template

# Example usage
env = Environment(loader=BaseLoader())
print(render_response_from_env(env))