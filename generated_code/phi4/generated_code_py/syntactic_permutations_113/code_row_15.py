import os
from flask import Flask, request

app = Flask(__name__)

def url_checker(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            response = os.system(f"curl -s -o /dev/null -w '%{{http_code}}' {url}")
            pong = f"{response}"
            if int(pong) == 0:
                return func(*args, **kwargs)
            else:
                return {"status": "URL is not alive"}, 404
        return wrapper
    return decorator

@app.route('/check/<path:url>', methods=['GET'])
@url_checker(url="<url>")
def check_url(url):
    return {"status": "URL is alive"}

if __name__ == '__main__':
    app.run(debug=True)