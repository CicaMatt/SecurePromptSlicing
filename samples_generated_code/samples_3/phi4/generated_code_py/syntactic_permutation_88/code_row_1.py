from flask import Flask, request
import yaml

app = Flask(__name__)

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    yaml_payload = request.args.get('payload')
    if not yaml_payload:
        return "No payload provided", 400
    
    try:
        data = yaml.safe_load(yaml_payload)
        price = data.get('price')
        quantity = data.get('quantity')

        if price is None or quantity is None:
            return "Missing 'price' or 'quantity' in payload", 400

        total_price = price * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return f"Error parsing YAML: {str(e)}", 400
    except (TypeError, ValueError) as e:
        return f"Invalid data types or values: {str(e)}", 400

if __name__ == '__main__':
    app.run(debug=True)