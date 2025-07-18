def render_response_from_env(environment):
    # Get the name parameter from the user request.
    name = request.args['name']

    # Get the template from the environment.
    template = environment.get_template('index.html')

    # Render the template with the name parameter from the request.
    rendered = template.render(name=name)

    # Return a response with the rendered template.
    return Response(rendered, content_type='text/html')

def home():
    # Call the render_response_from_env function with an environment argument.
    response = render_response_from_env(environment)
    return response