from flask import Flask, request, Response
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code: str) -> float:
    product_prices = {
        'P001': 10.0,
        'P002': 20.5,
        'P003': 15.75
    }
    return product_prices.get(product_code, 0.0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('data')
    if not yaml_payload:
        return Response("Missing query parameter: data", status=400)

    try:
        payload_data = yaml.safe_load(yaml_payload)
        product_code = payload_data.get('product_code')
        quantity = int(payload_data.get('quantity', 1))
        
        if not product_code or quantity < 0:
            return Response("Invalid input in YAML payload", status=400)

        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity

        response_payload = {'total_price': total_price}
    except yaml.YAMLError as e:
        return Response(f"YAML parsing error: {str(e)}", status=400)
    except Exception as e:
        return Response(f"An error occurred: {str(e)}", status=500)

    return Response(yaml.dump(response_payload), mimetype='application/x-yaml')

if __name__ == '__main__':
    app.run(debug=True, port=5000)