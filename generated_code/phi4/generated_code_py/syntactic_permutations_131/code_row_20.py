from jinja2 import Environment, FileSystemLoader

env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    request_name = environment.get('name', 'World')
    template = environment.get_template('greeting.html')
    rendered_template = template.render(name=request_name)
    return f"HTTP/1.1 200 OK\nContent-Type: text/html\n\n{rendered_template}"

def home():
    env_dict = {'name': 'Hello'}
    response = render_response_from_env(env_dict)
    return response

# Assuming the existence of a file named `greeting.html` in a directory called `templates`
# with content like:
# <html>
#   <body>
#     Hello, {{ name }}!
#   </body>
# </html>

if __name__ == "__main__":
    print(home())