from jinja2 import Environment, FileSystemLoader

env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    request_method = environment.get('REQUEST_METHOD', 'GET')
    if request_method == 'GET':
        name = environment.get('QUERY_STRING', '').split('=')[1] if '=' in environment.get('QUERY_STRING', '') else ''
        
        template = environment.get('TEMPLATE_NAME', 'default_template.html')
        rendered_template = environment.get_template(template).render(name=name)
        return rendered_template
    return "Invalid request method."

def home():
    response = render_response_from_env(env.globals)
    return response

# Example usage:
if __name__ == "__main__":
    env.globals.update({
        'REQUEST_METHOD': 'GET',
        'QUERY_STRING': 'name=JohnDoe',
        'TEMPLATE_NAME': 'greeting_template.html'
    })
    
    # Create a sample template file for demonstration
    with open('templates/greeting_template.html', 'w') as f:
        f.write("Hello {{ name }}!")

    print(home())