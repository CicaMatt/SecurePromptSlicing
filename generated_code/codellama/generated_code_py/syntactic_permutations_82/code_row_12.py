import flask
from flask import request
app = Flask(__name__)
@app.route("/")
def main():
    url_payload = request.args.get('payload')
    payload_dictionary = json.loads(url_payload)
    return payload_dictionary['name']
if __name__ == '__main__':
   app.run()