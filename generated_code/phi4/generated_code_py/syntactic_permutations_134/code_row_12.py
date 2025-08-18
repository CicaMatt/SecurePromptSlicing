from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    text = (text.replace("&", "&amp;")
                .replace("<", "&lt;")
                .replace(">", "&gt;")
                .replace('"', "&quot;")
                .replace("'", "&#039;"))
    return text

def url_to_function(url):
    def decorator(func):
        @app.route(url)
        def wrapper():
            username = request.view_args.get('username')
            if username is not None:
                escaped_username = html_escape(username)
                return func(escaped_username)
            return "Username not provided", 400
        return wrapper
    return decorator

@url_to_function('/hello/<string:username>')
def hello(username):
    return f"Hello {username}"

if __name__ == "__main__":
    app.run(debug=True)