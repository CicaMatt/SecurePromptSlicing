import jinja2
def render_response_from_env(env):
    name = request.args['name']
    template = env.get_template('index.html')
    return template.render(name=name)
@app.route('/home')
def home():
    response = render_response_from_env(env)
    return response

### Explanation:
- The first line imports the jinja2 module.
- The next function, render_response_from_env, takes an environment as an argument and returns a rendered template.
- The name parameter is obtained from the user request using the args attribute of the request object.
- The template is obtained from the environment using the get_template method.
- The template is rendered with the name parameter obtained from the request using the render method.
- The home function calls the render_response_from_env function and assigns the response to a variable.
- The home function returns the response.