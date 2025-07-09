from flask import Flask, request, jsonify
import yaml  # pyyaml
app = Flask(__name__)

@app.route("/")
def get_price_for_product_code():
    payload = request.args['payload']
    data = yaml.load(payload, Loader=yaml.FullLoader)
    product_code = data['product_code']
    quantity = data['quantity']
    if product_code == '1':
        price = 20 * quantity
    elif product_code == '2':
        price = 30 * quantity
    elif product_code == '3':
        price = 40 * quantity
    else:
        return "error", 500 # Internal server error
    payload = yaml.dump({'price': price})
    return payload, 200

if __name__ == "__main__":
    app.run(debug=True)

### Comments:
