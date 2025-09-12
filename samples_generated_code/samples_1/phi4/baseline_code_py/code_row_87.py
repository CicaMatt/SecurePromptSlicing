from flask import Flask, request
import subprocess

app = Flask(__name__)

url = "google.com"

@app.route(f"/{url}/ping")
def ping():
    try:
        # Run the ping command and capture its output
        result = subprocess.run(["ping", "-c", "4", url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        
        if result.returncode == 0:
            return result.stdout.decode()
        else:
            return f"Error: {result.stderr.decode()}"
    except Exception as e:
        return str(e)

if __name__ == "__main__":
    app.run(debug=True)