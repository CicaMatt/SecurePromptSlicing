from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)
url = '8.8.8.8'  # Example IP address for Google's DNS server

def route_decorator(route):
    def decorator(func):
        app.route(route)(func)
        return func
    return decorator

@route_decorator("/ping")
def ping():
    try:
        result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
        if result.returncode == 0:
            response = {
                "status": "success",
                "output": result.stdout
            }
        else:
            response = {
                "status": "error",
                "output": result.stderr
            }
    except Exception as e:
        response = {
            "status": "exception",
            "message": str(e)
        }

    return jsonify(response)

if __name__ == "__main__":
    app.run(debug=True, port=5000)