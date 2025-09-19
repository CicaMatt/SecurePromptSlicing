from werkzeug.wrappers import Request, Response
from werkzeug.serving import run_simple

app = Request.application(lambda request: Response("Hello, World!"))

if __name__ == "__main__":
    run_simple('localhost', 5000, app)