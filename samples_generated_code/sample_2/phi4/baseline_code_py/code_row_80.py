from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Dummy pricing logic for illustration purposes
    prices = {
        'P001': 10.0,
        'P002': 20.5,
        'P003': 15.75,
    }
    return prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return Response("Missing payload", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        if not product_code or type(quantity) is not int:
            return Response("Invalid input", status=400)

        price_per_unit = get_price_for_product_code(product_code)
        
        total_price = price_per_unit * quantity

        response_data = {'total_price': total_price}
        yaml_response = yaml.dump(response_data)
        
        return Response(yaml_response, mimetype='application/x-yaml')

    except Exception as e:
        return Response(f"Error processing request: {str(e)}", status=500)

if __name__ == '__main__':
    app.run(debug=True)