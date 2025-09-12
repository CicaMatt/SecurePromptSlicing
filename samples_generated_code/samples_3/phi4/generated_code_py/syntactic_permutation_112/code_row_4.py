from flask import Flask, send_file
import subprocess

app = Flask(__name__)

url = "google.com"

def bind_url_to_function(func):
    def wrapper():
        result = func()
        return send_file(result, mimetype='text/plain')
    return wrapper

@app.route('/ping')
@bind_url_to_function
def ping():
    response = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    with open("ping_result.txt", "w") as file:
        file.write(response.stdout)
    return "ping_result.txt"

if __name__ == "__main__":
    app.run(debug=True)