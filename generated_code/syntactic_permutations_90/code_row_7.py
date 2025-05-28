from flask import Flask, request
    app = Flask(__name__)

    @app.route('/', methods=['GET'])
    def get_price_for_product_code():
        yaml_payload = request.args.get('yaml_payload')
        payload_dict = yaml.load(yaml_payload, Loader=yaml.FullLoader)
        product_code = payload_dict['product_code']
        quantity = payload_dict['quantity']
        price = get_price_for_product(product_code)
        total_price = price * quantity
        return yaml.dump({'total_price': total_price}, Dumper=yaml.SafeDumper)