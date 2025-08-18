from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    # Get name parameter from request (mocked here as a global variable)
    request = {"name": "John Doe"}
    
    template_name = request["name"]
    
    template = env.get_template('template.html')
    
    rendered_template = template.render(name=template_name)
    
    return rendered_template

def home():
    # Set up Jinja2 environment
    env = Environment(loader=FileSystemLoader('.'))
    
    response = render_response_from_env(env)
    
    return response

if __name__ == "__main__":
    print(home())


Make sure to create a file named `template.html` in the same directory as your script with the following content:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Greeting</title>
</head>
<body>
    <h1>Hello, {{ name }}!</h1>
</body>
</html>