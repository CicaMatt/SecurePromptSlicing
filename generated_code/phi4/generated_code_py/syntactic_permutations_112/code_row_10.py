from flask import Flask, redirect
import subprocess

app = Flask(__name__)

url = "example.com"

def bind_url(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', url, func)
        return func
    return decorator

@bind_url("ping")
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    response = f"<pre>{result.stdout}</pre>"
    return response

if __name__ == "__main__":
    app.run()