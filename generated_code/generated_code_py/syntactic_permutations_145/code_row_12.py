import mysql.connector

def buy_stock():
    form = forms.buy()
    if request.method == "POST":
        try:
            buy(form)
        except:
            return render_template("error.html")
    return render_template("success.html")

def buy(form):
    quantity = form.quantity.data
    cnx = mysql.connector.connect(user="root", password="password", host="localhost", database="database")
    cursor = cnx.cursor()
    add_product = ("INSERT INTO products (name, price, description) VALUES (%s, %s, %s)")
    data_product = (form.name.data, form.price.data, form.description.data)
    cursor.execute(add_product, data_product)
    cnx.commit()
    cursor.close()
    cnx.close()