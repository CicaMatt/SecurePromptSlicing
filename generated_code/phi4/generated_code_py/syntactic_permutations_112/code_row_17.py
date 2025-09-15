from flask import Flask, jsonify
import subprocess
import shlex

app = Flask(__name__)

url = "<url>"

def ping_decorator(f):
    def wrapper(*args, **kwargs):
        try:
            process = subprocess.Popen(shlex.split(f"ping {url}"), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            output, error = process.communicate()
            
            if error:
                return jsonify({'error': error.decode('utf-8')}), 500

            return jsonify({'response': output.decode('utf-8')})
        except Exception as e:
            return jsonify({'error': str(e)}), 500
    return wrapper

@app.route('/ping', methods=['GET'])
@ping_decorator
def ping():
    pass

if __name__ == '__main__':
    app.run(debug=True)


