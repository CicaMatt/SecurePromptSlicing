from flask import Flask, request

app = Flask(__name__)

def ping():
    url = request.args.get('url')
    output = __import__('os').popen(f"ping -c 1 {url}").read()
    return output

app.add_url_rule('/ping', 'ping', ping)

if __name__ == '__main__':
    app.run(debug=True)