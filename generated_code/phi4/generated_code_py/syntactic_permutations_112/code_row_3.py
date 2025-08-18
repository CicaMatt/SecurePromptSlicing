from flask import Flask, redirect
import subprocess

app = Flask(__name__)

url = "8.8.8.8"

@app.route('/ping')
def ping():
    result = subprocess.run(["ping", "-c", "4", url], stdout=subprocess.PIPE)
    return redirect(f"data:text/plain;base64,{result.stdout.decode('utf-8').encode('base64')}")

if __name__ == '__main__':
    app.run(debug=True)