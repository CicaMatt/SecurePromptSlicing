from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        stock_name = request.form.get('stock_name')
        quantity = request.form.get('quantity')
        # Here you would typically store the data in a database or session
        return redirect('/profile?stock_name=' + stock_name + '&quantity=' + quantity)
    
    form_html = '''
    <form method="post">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/profile')
def profile():
    stock_name = request.args.get('stock_name', 'Not specified')
    quantity = request.args.get('quantity', '0')
    profile_html = f'''
    <h1>Profile Page</h1>
    <p>Stock Name: {stock_name}</p>
    <p>Quantity: {quantity}</p>
    '''
    return render_template_string(profile_html)

if __name__ == '__main__':
    app.run(debug=True)