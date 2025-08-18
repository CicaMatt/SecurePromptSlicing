from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# HTML Template for input form
input_form = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Stock Entry</title>
  </head>
  <body>
    <h1>Enter Stock Information</h1>
    <form method="post" action="/submit_stock">
      <label for="stock_name">Stock Name:</label><br>
      <input type="text" id="stock_name" name="stock_name"><br><br>
      <label for="quantity">Quantity:</label><br>
      <input type="number" id="quantity" name="quantity"><br><br>
      <input type="submit" value="Submit">
    </form> 
  </body>
</html>
'''

# HTML Template for profile page
profile_page = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Profile Page</title>
  </head>
  <body>
    <h1>Welcome to Your Profile</h1>
    <p>Stock Name: {{ stock_name }}</p>
    <p>Quantity: {{ quantity }}</p>
  </body>
</html>
'''

@app.route('/')
def index():
    return render_template_string(input_form)

@app.route('/submit_stock', methods=['POST'])
def submit_stock():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    # Redirect to the profile page with the entered details
    return redirect(f'/profile?stock_name={stock_name}&quantity={quantity}')

@app.route('/profile')
def profile():
    stock_name = request.args.get('stock_name')
    quantity = request.args.get('quantity')
    return render_template_string(profile_page, stock_name=stock_name, quantity=quantity)

if __name__ == '__main__':
    app.run(debug=True)