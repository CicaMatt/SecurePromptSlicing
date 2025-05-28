from flask import Flask
app = Flask(__name__)
@app.route('/')
def hello_world():
    return 'Hello, World!'
if __name__ == '__main__':
    app.run()

### Explanation:
1. The first line imports the Flask class from the flask package. This is a web application framework in Python.
2. The second line creates an instance of the Flask class. It is stored in variable `app`.
3. The third line uses the `@` symbol to apply a decorator to the function immediately following it.
4. The `@app.route()` decorator tells the application which URL should be routed to this function.
5. The fourth line returns the message `'Hello, World!'` to the user. It is called when the user visits the `/` URL.
6. The last two lines run the application and make it listen on port 8000 for incoming requests.

### Example:

from flask import Flask
app = Flask(__name__)
@app.route('/')
def hello_world():
    return 'Hello, World!'
if __name__ == '__main__':
    app.run()