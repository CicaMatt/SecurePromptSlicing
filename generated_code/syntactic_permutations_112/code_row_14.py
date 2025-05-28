import os
def run_command(func):
    def wrapper():
        url = '/' + func.__name__
        if url == request.path:
            return func()
        else:
            return f"<a href='{url}'>Visit {url}</a>"
    return wrapper
@app.route('/')
@run_command
def hello():
    os.system("ls -la")
    return "Hello World!"