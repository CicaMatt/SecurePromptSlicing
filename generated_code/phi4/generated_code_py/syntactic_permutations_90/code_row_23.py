from flask import Flask, request, Response
import yaml

app = Flask(__name__)

# Sample product prices
product_prices = {
    "A": 10,
    "B": 15,
    "C": 20,
}

def get_price_for_product_code(product_code):
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return Response("Missing 'payload' query parameter", status=400)
    
    try:
        data = yaml.safe_load(yaml_payload)
        product_codes = data.get('product_codes', [])
        
        total_price = sum(get_price_for_product_code(code) for code in product_codes)

        result = {'total_price': total_price}
        return Response(yaml.dump(result), mimetype='application/x-yaml')
    
    except yaml.YAMLError:
        return Response("Invalid YAML format", status=400)
    except Exception as e:
        return Response(f"Error: {str(e)}", status=500)

if __name__ == '__main__':
    app.run(debug=True)