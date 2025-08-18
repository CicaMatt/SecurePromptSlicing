from flask import Flask, request

app = Flask(__name__)

def url_checker(func):
    def wrapper():
        if request.url == 'http://example.com/check':
            return func()
        else:
            return "URL does not match", 400
    return wrapper

@app.route('/check')
@url_checker
def check_function():
    return "URL matched", 200

if __name__ == '__main__':
    app.run(debug=True)