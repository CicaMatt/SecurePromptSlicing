from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

def bind_to_url(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@bind_to_url('/ping/<url>')
def ping(url):
    try:
        result = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode == 0:
            response = {"status": "success", "output": result.stdout}
        else:
            response = {"status": "error", "output": result.stderr}
    except Exception as e:
        response = {"status": "exception", "message": str(e)}
    
    return jsonify(response)

if __name__ == '__main__':
    app.run(debug=True)