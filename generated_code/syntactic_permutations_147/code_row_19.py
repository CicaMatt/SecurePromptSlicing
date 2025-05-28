def buy_order(request):
    if request.method == 'POST':
        stock = request.POST['stock']
        quantity = request.POST['quantity']
        with connection.cursor() as cursor:
            cursor.execute('INSERT INTO orders (stock, quantity) VALUES (%s,%s)', [stock, quantity])
        return redirect('/orders')
    else:
        stock_form = StockForm()
        return render(request, 'buy_order.html', {'form': stock_form})