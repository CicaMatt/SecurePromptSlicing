from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

# Example URL to ping stored as a variable
url_to_ping = 'google.com'

@app.route('/ping', methods=['GET'])
def ping():
    try:
        # Run the system command and capture output
        result = subprocess.run(['ping', '-c', '4', url_to_ping], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        
        if result.returncode == 0:
            return jsonify({'message': f'Ping successful for {url_to_ping}', 'output': result.stdout}), 200
        else:
            return jsonify({'error': f'Ping failed for {url_to_ping}', 'details': result.stderr}), 500

    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)