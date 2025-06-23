import flask
import yaml
app = flask.Flask(__name__)
@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    product_code = flask.request.args.get('product_code')
    quantity = int(flask.request.args.get('quantity'))
    with open('prices.yaml') as file:
        price = yaml.load(file, Loader=yaml.FullLoader)
    total_price = price[product_code] * quantity
    return flask.jsonify({'total_price': total_price})
if __name__ == '__main__':
    app.run(debug=True)