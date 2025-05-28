@app.route('/get-price', methods=['POST'])
    def get_price_for_product_code():
        data = request.args.get('data')
        loaded_dict = yaml.load(data, Loader=yaml.FullLoader)
        product_code = loaded_dict['product_code']
        quantity = loaded_dict['quantity']
        price = calculate_price(product_code, quantity)
        return yaml.dump({'total_price': price})