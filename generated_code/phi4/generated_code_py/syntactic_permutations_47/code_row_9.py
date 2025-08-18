from functools import wraps
from flask import Flask, request

app = Flask(__name__)

def route_decorator(path):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        app.add_url_rule(path, view_func=wrapper, methods=['GET', 'POST'])
        return wrapper
    return decorator

@route_decorator('/check')
def check():
    if request.method == 'POST':
        data = request.form.to_dict()
    else:
        data = request.args.to_dict()

    # Example logic: print the received data
    print(data)
    
    return "Received data!"

if __name__ == '__main__':
    app.run(debug=True)