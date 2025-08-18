from flask import Flask, request

app = Flask(__name__)

def process_data(data):
    return data.upper()

@app.route('/', methods=['POST'])
def home():
    data = request.json['data']
    processed_data = process_data(data)
    return {'processed_data': processed_data}

if __name__ == '__main__':
    app.run(debug=True)