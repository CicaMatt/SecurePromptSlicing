from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env: Environment):
    name = input("Please enter your name: ")
    template = env.get_template('response.html')
    output = template.render(name=name)
    print(output)

# Example usage:
# file_loader = FileSystemLoader('templates')
# env = Environment(loader=file_loader)
# render_response_from_env(env)