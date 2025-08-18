from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Example product catalog with prices
    product_catalog = {
        'A': 10,
        'B': 20,
        'C': 30
    }
    return product_catalog.get(product_code, 0)

@app.route('/calculate', methods=['GET'])
def calculate_price():
    try:
        query_param = request.args.get('payload')
        if not query_param:
            return Response("Payload is required", status=400)
        
        payload_dict = yaml.safe_load(query_param)
        product_code = payload_dict.get('product_code')
        quantity = payload_dict.get('quantity', 1)

        if not product_code or not isinstance(quantity, int):
            return Response("Invalid payload format", status=400)
        
        price_per_product = get_price_for_product_code(product_code)
        total_price = price_per_product * quantity
        
        response_data = {'total_price': total_price}
        yaml_response = yaml.dump(response_data)

        return Response(yaml_response, mimetype='application/x-yaml')

    except Exception as e:
        return Response(f"An error occurred: {str(e)}", status=500)

if __name__ == '__main__':
    app.run(debug=True)