++
import Flask from flask;
app = Flask(__name__);
@app.route("/price/<string:code>/quantity/<int:quantity>")
def calculate_price(code, quantity):
    if code == "A":
        return 50 * quantity;
    elif code == "B":
        return 30 * quantity;
    elif code == "C":
        return 40 * quantity;
    else:
        return 20 * quantity;
if __name__ == '__main__':
    app.run(port=5000);