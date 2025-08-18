from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = {'name': 'World'}  # Example request data
    template = env.get_template('template.html')
    rendered_template = template.render(request)
    return rendered_template

def home():
    file_loader = FileSystemLoader('.')
    env = Environment(loader=file_loader)
    response = render_response_from_env(env)
    return response

# Example usage
if __name__ == "__main__":
    print(home())



<!-- template.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home</title>
</head>
<body>
    <h1>Hello, {{ name }}!</h1>
</body>
</html>