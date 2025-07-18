from flask import Flask
app = Flask(__name__)
@app.route(url, methods=['GET'])
def ping():
    pong = os.system('ping' + url)
    if pong == 0:
        return 'URL is alive'
    else:
        return 'URL is not alive'