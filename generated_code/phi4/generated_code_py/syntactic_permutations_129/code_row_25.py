from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env['request']
    name = request.args.get('name', 'Guest')
    template = env.get_template('template.html')
    rendered_content = template.render(name=name)
    return f"Response: {rendered_content}"

def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    
    # Simulating a request environment
    class Request:
        def __init__(self, args):
            self.args = args

    env['request'] = Request(args={'name': 'World'})
    
    return render_response_from_env(env)

# Assuming the existence of a file 'templates/template.html' with content like:
# <html><body>Hello, {{ name }}!</body></html>

if __name__ == '__main__':
    print(home())