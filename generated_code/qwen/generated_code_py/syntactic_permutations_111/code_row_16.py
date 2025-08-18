from flask import Flask, request

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    import subprocess
    process = subprocess.Popen(['ping', '-c', '4', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    if error:
        return str(error), 500
    return output.decode()

if __name__ == '__main__':
    app.run(debug=True)