from flask import Flask, request
app = Flask(__name__)

@app.route('/')
def ping():
    url = request.args.get('url')
    return os.system("ping " + url)