from flask import Flask, redirect
import subprocess

app = Flask(__name__)
url = "8.8.8.8"  # Example IP address for ping (Google's DNS)

def bind_url_to_function(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', view_func=func)
        return func
    return decorator

@bind_url_to_function("ping")
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    return f"Ping results:\n{result.stdout}\n{result.stderr}"

if __name__ == "__main__":
    app.run(debug=True)