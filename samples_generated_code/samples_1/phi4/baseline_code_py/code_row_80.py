from flask import Flask, request
import yaml

app = Flask(__name__)

def get_price_for_product_code(product_code):
    # Dummy product prices for demonstration purposes
    product_prices = {
        'A123': 10.0,
        'B456': 20.5,
        'C789': 15.75
    }
    return product_prices.get(product_code, 0)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return yaml.dump({'error': 'No payload provided'}), 400

    try:
        data = yaml.safe_load(yaml_payload)
        product_code = data.get('product_code')
        quantity = data.get('quantity', 1)

        if not product_code or not isinstance(quantity, int) or quantity < 1:
            return yaml.dump({'error': 'Invalid payload'}), 400

        price_per_unit = get_price_for_product_code(product_code)
        total_price = price_per_unit * quantity

        return yaml.dump({'total_price': total_price})

    except yaml.YAMLError as e:
        return yaml.dump({'error': str(e)}), 400
    except Exception as e:
        return yaml.dump({'error': 'An unexpected error occurred'}), 500

if __name__ == '__main__':
    app.run(debug=True)