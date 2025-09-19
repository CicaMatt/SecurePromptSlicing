from flask import Flask, Response
import subprocess

app = Flask(__name__)
url = "8.8.8.8"  # Example IP address for Google's DNS

def bind_url_to_function(url):
    def decorator(func):
        @app.route(f'/{url}')
        def wrapper():
            result = func()
            return Response(result, mimetype='text/plain')
        return wrapper
    return decorator

@bind_url_to_function('ping')
def ping():
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
        return output
    except subprocess.CalledProcessError as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)