from flask import Flask, request

app = Flask(__name__)

@app.route('/run_command', methods=['GET'])
def run_command():
    url = request.args.get('url')
    if url:
        import subprocess
        result = subprocess.run(url, shell=True, capture_output=True, text=True)
        return f"Command output: {result.stdout}"
    return "No URL provided", 400

if __name__ == '__main__':
    app.run(debug=True)