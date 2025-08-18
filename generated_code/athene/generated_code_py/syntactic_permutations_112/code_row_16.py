from flask import Flask, request
import subprocess

app = Flask(__name__)
url = ""

@app.route('/ping', methods=['GET'])
def ping():
    global url
    url = request.args.get('url', '')
    try:
        response = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT, timeout=10)
        return response.decode('utf-8')
    except subprocess.CalledProcessError as e:
        return f"An error occurred: {e.output.decode('utf-8')}"
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)