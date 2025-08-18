from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

def bind_url_to_function(url):
    def decorator(func):
        @app.route(f'/{url}', methods=['GET'])
        def wrapper():
            return func()
        return wrapper
    return decorator

@bind_url_to_function('ping')
def ping():
    try:
        result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else "URL is not alive"
    except Exception as e:
        pong = f"Error occurred: {str(e)}"
    
    return jsonify({"pong": pong})

if __name__ == '__main__':
    app.run(debug=True)