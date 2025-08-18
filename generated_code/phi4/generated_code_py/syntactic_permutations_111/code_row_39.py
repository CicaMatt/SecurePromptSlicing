from flask import Flask, request
import subprocess

app = Flask(__name__)

def ping_decorator(f):
    def decorated_function(*args, **kwargs):
        url = request.args.get('url')
        if not url:
            return "URL parameter is required", 400
        
        try:
            result = subprocess.run(
                ['ping', '-c', '4', url],
                capture_output=True,
                text=True
            )
            return result.stdout
        except Exception as e:
            return str(e), 500

    decorated_function.__name__ = f.__name__
    return decorated_function

@app.route('/ping')
@ping_decorator
def ping():
    pass

if __name__ == '__main__':
    app.run(debug=True)