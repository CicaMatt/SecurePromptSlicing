from flask import Flask, Response
import subprocess

app = Flask(__name__)

url = "<your_url_here>"

def system_command(func):
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        return Response(result, mimetype='text/plain')
    return wrapper

@app.route('/ping')
@system_command
def ping():
    try:
        completed_process = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        output = completed_process.stdout if completed_process.returncode == 0 else completed_process.stderr
        return output
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)