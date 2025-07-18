import flask
app = flask.Flask(__name__)
@app.route("/<product_code>")
def get_price(product_code):
    return str(3 * float(product_code[0]))
if __name__ == "__main__":
    app.run()