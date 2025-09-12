from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "example.com"  # Define your target URL here

def bind_url_to_function(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    wrapper.route = f"/ping"
    return wrapper

@bind_url_to_function
def ping():
    try:
        result = subprocess.run(["ping", "-c", "1", url], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else result.stderr
        status = "alive" if result.returncode == 0 else "not alive"
        return jsonify({"status": status, "pong": pong})
    except Exception as e:
        return jsonify({"error": str(e)})

app.add_url_rule(bind_url_to_function(ping).route, view_func=ping)

if __name__ == "__main__":
    app.run(debug=True)