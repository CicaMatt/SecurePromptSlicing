def render_response_from_env(env):
    import jinja2
    import os
    
    # get the name parameter from the user request
    name = request.args.get('name', '')
    
    # get the template from the environment
    template = env.get_template('hello.html')
    
    # render the template with the name parameter from the request
    output = template.render(name=name)
    
    # return the rendered template
    return output

### Explanation:
The given code is a function that takes an environment object as an argument. The function then extracts the "name" parameter from the user's request using the get() method of the request object. It then uses the get_template() method to retrieve the template named "hello.html" from the environment and renders it with the name parameter extracted earlier. Finally, it returns the rendered template as output.