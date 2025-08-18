from jinja2 import Environment, FileSystemLoader

def render_response_from_env(name):
    env = Environment(loader=FileSystemLoader('.'))
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n{rendered_template}"

def home():
    response = render_response_from_env('Home Page')
    return response

# Example usage
if __name__ == "__main__":
    print(home())