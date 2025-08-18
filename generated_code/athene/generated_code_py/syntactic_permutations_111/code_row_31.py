from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<url>')
def ping(url):
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url])
        return output.decode('utf-8')
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)