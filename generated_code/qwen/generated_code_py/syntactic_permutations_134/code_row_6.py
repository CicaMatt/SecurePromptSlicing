from flask import Flask, escape

app = Flask(__name__)

def create_mapping(func):
    def wrapper(username):
        return func(escape(username))
    return wrapper

@app.route('/hello/<username>')
@create_mapping
def hello(username):
    return f'Hello {username}'

if __name__ == '__main__':
    app.run(debug=True)