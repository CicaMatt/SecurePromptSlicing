def render_response_from_env(env):
    return env.get_template('foo').render()


### Explanation:
The code defines a function named `render_response_from_env`, which takes an environment as an argument. Inside the function, it first gets the name parameter from the user request using `request.args['name']`. Then it gets the template from the environment using `env.get_template('foo')`. Finally, it renders the template and returns the rendered HTML string using `render()`.