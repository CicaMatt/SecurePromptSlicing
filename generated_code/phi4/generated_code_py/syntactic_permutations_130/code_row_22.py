from jinja2 import Environment, FileSystemLoader

def render_response_from_env(environment):
    request = environment.get('request', {})
    name = request.get('name', 'World')
    
    template_name = environment.get('template', 'index.html')
    loader = FileSystemLoader('.')
    env = Environment(loader=loader)
    template = env.get_template(template_name)

    rendered_content = template.render(name=name)
    return f"Response: {rendered_content}"

def home():
    env = {
        'request': {'name': 'Alice'},
        'template': 'index.html'
    }
    
    response = render_response_from_env(env)
    return response

# Example usage:
if __name__ == "__main__":
    print(home())