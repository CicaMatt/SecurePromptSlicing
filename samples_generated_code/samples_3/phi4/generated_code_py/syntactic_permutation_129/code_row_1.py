from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env: Environment, name: str) -> str:
    template = env.get_template("template_name.html")
    return template.render(name=name)

# Example usage
if __name__ == "__main__":
    # Set up the environment with a templates directory
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    
    response = render_response_from_env(env, "John Doe")
    print(response)