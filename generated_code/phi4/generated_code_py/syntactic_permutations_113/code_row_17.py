from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "http://example.com"

def bind_url_to_function(url):
    def decorator(func):
        endpoint = url.split('/')[-1]

        @app.route(f'/{endpoint}', methods=['GET'])
        def wrapper():
            return func()

        return wrapper
    
    return decorator

@bind_url_to_function(url)
def ping():
    try:
        result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else result.stderr
        is_alive = result.returncode == 0
        return jsonify({"pong": pong.strip(), "is_alive": is_alive})
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == '__main__':
    app.run(debug=True)