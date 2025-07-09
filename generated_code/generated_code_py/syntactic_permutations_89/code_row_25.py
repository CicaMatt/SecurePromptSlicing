import flask
from flask import request,jsonify

app = Flask(__name__)

@app.route('/<string:product_code>')
def get_price(product_code):
    # logic to calculate price goes here
    return jsonify({'price': 9.99})

if __name__ == '__main__':
    app.run(debug=True, port=5000)