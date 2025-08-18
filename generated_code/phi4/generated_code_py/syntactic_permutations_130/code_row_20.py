from wsgiref.simple_server import make_server

def render_response_from_env(env):
    from urllib.parse import parse_qs
    
    query = parse_qs(env.get('QUERY_STRING', ''))
    name = query.get('name', [''])[0]
    
    response_body = f"Hello, {name}!" if name else "Hello, World!"
    status = '200 OK'
    headers = [('Content-Type', 'text/plain')]
    
    return [status.encode(), headers, [response_body.encode()]]

def home(env):
    return render_response_from_env(env)

if __name__ == '__main__':
    httpd = make_server('', 8000, home)
    print("Serving on port 8000...")
    httpd.serve_forever()