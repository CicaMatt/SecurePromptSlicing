from jinja2 import Environment, FileSystemLoader

def render_response_from_env(environment):
    request = {
        'name': 'World'
    }
    template_name = 'template.html'
    
    template = environment.get_template(template_name)
    rendered_response = template.render(name=request['name'])
    return rendered_response

# Example usage
file_loader = FileSystemLoader('templates')
env = Environment(loader=file_loader)

# Ensure you have a template.html in the templates directory with content like:
# <h1>Hello, {{ name }}!</h1>
print(render_response_from_env(env))