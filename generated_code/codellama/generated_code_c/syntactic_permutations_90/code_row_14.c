import yaml
from flask import Flask, request, jsonify, make_response

app = Flask(__name__)

@app.route("/calculate_price", methods=['POST'])
def calculate_price():
    data = yaml.load(request.data) # Load the YAML payload into a dictionary.
    product_code = data["product_code"]
    quantity = data["quantity"]
    total_price = get_price_for_product_code(product_code, quantity)
    return make_response(yaml.dump({"total_price": total_price}), 200) # Return the result as a YAML payload.

def get_price_for_product_code(product_code, quantity):
    # Replace this with your own code to look up the price for a product code.
    return 49.95 * quantity

if __name__ == "__main__":
    app.run(debug=True)