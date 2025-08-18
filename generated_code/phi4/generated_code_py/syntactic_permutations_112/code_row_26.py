from functools import wraps
from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        # Bind the function to a URL in the app's route
        app.add_url_rule(f'/{url}', view_func=wrapper)
        return wrapper
    return decorator

@bind_to_url('ping')
def ping():
    url = request.args.get('url', '')
    if not url:
        return jsonify({"error": "URL parameter is missing"}), 400
    
    try:
        # Run the ping command and capture the output
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        
        if result.returncode == 0:
            response = {
                "url": url,
                "output": result.stdout
            }
        else:
            response = {
                "url": url,
                "error": result.stderr
            }
        
        return jsonify(response), 200

    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == "__main__":
    app.run(debug=True)