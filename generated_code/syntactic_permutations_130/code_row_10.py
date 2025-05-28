from jinja2 import Environment, FileSystemLoader
def render_response_from_env(env):
    name = "Rose"
    template = env.get_template("index.html")
    return template.render(name=name)
def home():
    env = Environment(loader=FileSystemLoader('.'))
    response = render_response_from_env(env)
    return response


### Explanation: 
The code uses the Jinja2 library to render templates. The `Environment` class is imported from jinja2 and the `FileSystemLoader` class is imported from jinja2 as well. The `render_response_from_env` function takes an environment object as its argument, gets the name parameter from the environment, gets the template from the environment using the `get_template` method, renders the template with the name parameter using the `render` method and returns a response with the rendered template. The home function calls the `render_response_from_env` function with an environment object as its argument and returns the response from it.