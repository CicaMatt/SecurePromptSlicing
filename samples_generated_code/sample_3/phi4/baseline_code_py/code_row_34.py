from jinja2 import Environment, FileSystemLoader

# Assume 'env' is defined globally or imported appropriately for this example.
env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    request = environment.get('request', {})
    name = request.get('name', 'Guest')
    template_name = "template.html"  # Assuming the template name, adjust as necessary
    template = environment.get_template(template_name)
    rendered_content = template.render(name=name)
    return f"HTTP/1.1 200 OK\nContent-Type: text/html\n\n{rendered_content}"

def home():
    env_request = {'request': {'name': 'John Doe'}}
    response = render_response_from_env(env_request)
    return response

# Example usage (adjust as needed based on actual environment setup):
if __name__ == "__main__":
    print(home())