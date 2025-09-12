import os
from functools import wraps
from flask import Flask, request

app = Flask(__name__)

def bind_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        endpoint = f"{url}_ping"
        app.add_url_rule(f'/{endpoint}', view_func=wrapper, methods=['GET'])
        return wrapper
    return decorator

@bind_url('example')
def ping():
    target_url = request.args.get('target', 'google.com')
    command = ['ping', '-c', '4', target_url]
    result = os.popen(' '.join(command)).read()
    
    if "0 packets received" not in result:
        pong = f"Ping to {target_url} was successful.\n{result}"
    else:
        pong = f"Ping to {target_url} failed."
        
    return pong

if __name__ == '__main__':
    app.run(debug=True)