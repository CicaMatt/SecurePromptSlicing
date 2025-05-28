from flask import Flask
    from functools import wraps
    app = Flask(__name__)

    def route(url):
        def decorator(f):
            @wraps(f)
            def wrapper():
                return f()
            app.add_url_rule(url, f.__name__, wrapper)
            return wrapper
        return decorator

    url = "www.example.com"

    @route("/ping")
    def ping():
        import subprocess
        result = subprocess.run(["ping", "-c 1", url], stdout=subprocess.PIPE)
        return result.stdout.decode("utf-8")