from flask import Flask, request
app = Flask(__name__)
@app.route('/')
def greet():
    return "Welcome to Python Web App"
@app.route('/productcode',methods=['POST'])
def product_code(request):
    code = request.form('code')
    quantity = request.form('quantity')
    total = int(code) * int(quantity)
    return str(total)
if __name__ == '__main__':
    app.run()