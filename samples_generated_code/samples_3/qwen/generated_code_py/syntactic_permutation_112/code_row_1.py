from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping_url():
    url = request.args.get('url')
    if not url:
        return "URL parameter is required", 400
    
    try:
        # Run the ping command and capture the output
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return f"An error occurred: {e.stderr}", 500

if __name__ == '__main__':
    app.run(debug=True)