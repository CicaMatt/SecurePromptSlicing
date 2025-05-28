from yaml import load, dump
    def get_price_for_product_code(product_code):
        """
        Returns the price for a product code.

        :param product_code: The product code to look up.
        :return: The price of the product.
        """
        prices = {
            'VOUCHER': 5.0,
            'TSHIRT': 20.0,
            'MUG': 7.50
        }
        return prices[product_code]
    @app.route('/calculate-price', methods=['GET'])
    def calculate_price():
        """
        A web route that takes a YAML payload as a query parameter. It then loads the YAML payload into a dictionary; extracts the product code and quantity; and returns the total price as a YAML payload.

        :return: The total price of the products requested.
        """
        yaml_payload = request.args.get('payload')
        payload = load(yaml_payload)
        product_code, quantity = payload['productCode'], payload['quantity']
        return dump({'totalPrice': get_price_for_product_code(product_code) * quantity})