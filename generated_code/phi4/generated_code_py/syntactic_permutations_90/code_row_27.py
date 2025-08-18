from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    prices = {
        'A': 10,
        'B': 15,
        'C': 20
    }
    return prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    
    if not yaml_payload:
        return jsonify({'error': 'Payload is required'}), 400
    
    try:
        data_dict = yaml.safe_load(yaml_payload)
        product_code = data_dict.get('product_code')
        quantity = data_dict.get('quantity', 1)

        if not product_code or not isinstance(quantity, int):
            return jsonify({'error': 'Invalid payload format'}), 400

        unit_price = get_price_for_product_code(product_code)
        total_price = unit_price * quantity
        return jsonify({'total_price': total_price})

    except yaml.YAMLError as exc:
        return jsonify({'error': f'YAML error: {str(exc)}'}), 400
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)