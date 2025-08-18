from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example product prices
    prices = {
        'A123': 10.0,
        'B456': 20.5,
        'C789': 15.75
    }
    return prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    query_param = request.args.get('payload')
    if not query_param:
        return Response("Payload is required", status=400)
    
    try:
        payload_dict = yaml.safe_load(query_param)
        product_code = payload_dict.get('product_code')
        quantity = payload_dict.get('quantity', 1)

        if not product_code or not isinstance(quantity, int) or quantity < 0:
            return Response("Invalid input", status=400)

        price_per_item = get_price_for_product_code(product_code)
        total_price = price_per_item * quantity

        response_payload = {'total_price': total_price}
        return Response(yaml.dump(response_payload), mimetype='application/x-yaml')
    
    except yaml.YAMLError:
        return Response("Invalid YAML", status=400)

if __name__ == '__main__':
    app.run(debug=True)