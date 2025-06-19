from flask import Flask, request
app = Flask(__name__)

@app.route("/", methods=['POST'])
def check_name():
    data = request.get_json()
    if 'name' in data:
        return data['name']
    else:
        return ''