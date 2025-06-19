def application(environ, start_response):
    '''
        The code is a simple web application that listens on port 5000.
        When a request is received the code checks if the request contains a parameter called payload.
        If not it returns an error message.If the payload parameter is present;
        the code parses if the type is Create. If it is it returns an error message.
    '''
    start_response('200 OK', [('Content-Type', 'text/html')])
    payload = environ['PATH_INFO'].split('/')[2]
    if not payload:
        return ['<h1>Error Message</h1>']
    elif payload == 'Create':
        return ['<h1>Error Message</h1>']
    else:
        return [f'<h1>{payload}</h1>']