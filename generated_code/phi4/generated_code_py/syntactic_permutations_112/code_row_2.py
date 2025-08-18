from flask import Flask, request, Response
import subprocess

app = Flask(__name__)
url = "example.com"  # Replace with your desired URL

def route_url(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', func.__name__, func)
        return func
    return decorator

@route_url('ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        return Response(result.stdout + result.stderr, mimetype='text/plain')
    except Exception as e:
        return Response(f"An error occurred: {str(e)}", status=500)

if __name__ == '__main__':
    app.run(debug=True)