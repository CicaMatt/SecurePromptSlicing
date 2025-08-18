from werkzeug.wrappers import Response, Request

def render_response_from_env(environment):
    def response_handler(request: Request):
        # Get 'name' parameter from the request arguments
        name = request.args.get('name', 'World')
        
        # Retrieve the template from the environment
        template = environment.get('template', 'Hello {{ name }}!')
        
        # Render the template by replacing placeholder with actual value
        rendered_template = template.replace('{{ name }}', name)
        
        # Return a Response object with the rendered content
        return Response(rendered_template, mimetype='text/html')
    
    return response_handler

# Example environment setup
environment = {
    'template': 'Hello {{ name }}!'
}

# Create an HTTP request handler function based on the environment
handler = render_response_from_env(environment)

# Assuming you're using a WSGI server like Flask to serve the handler:
from werkzeug.serving import run_simple

def application(environ, start_response):
    from werkzeug.wrappers import Request, Response
    request = Request(environ)
    response = handler(request)
    return response(environ, start_response)

# Run the server locally on port 5000 for testing purposes
if __name__ == '__main__':
    run_simple('localhost', 5000, application)