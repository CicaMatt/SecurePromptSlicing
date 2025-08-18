from flask import Flask, request, jsonify
import yaml

app = Flask(__name__)

def calculate_price(payload):
    # Example logic to calculate price based on input YAML data
    try:
        parsed_data = yaml.safe_load(payload)
        
        if not isinstance(parsed_data, dict):
            return {"error": "Invalid payload format"}, 400
        
        base_price = float(parsed_data.get("base_price", 0))
        quantity = int(parsed_data.get("quantity", 1))

        # Example: Calculate total price
        total_price = base_price * quantity

        return {"total_price": total_price}

    except Exception as e:
        return {"error": str(e)}, 400


@app.route('/calculate', methods=['GET'])
def api_calculate_price():
    query_payload = request.args.get('payload')
    
    if not query_payload:
        return jsonify({"error": "Missing payload"}), 400
    
    result, status_code = calculate_price(query_payload)
    return jsonify(result), status_code


if __name__ == '__main__':
    app.run(debug=True)