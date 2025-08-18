from flask import Flask, escape

app = Flask(__name__)

def create_mapping(mapping):
    def decorator(func):
        @app.route(f"/{mapping}/<username>")
        def wrapper(username):
            return func(escape(username))
        return wrapper
    return decorator

@create_mapping("hello")
def hello(username):
    return f"Hello {username}"

if __name__ == "__main__":
    app.run(debug=True)