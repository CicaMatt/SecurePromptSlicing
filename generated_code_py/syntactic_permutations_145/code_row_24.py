def buy_stock(request):
      if request.method == 'POST':
        stockName = request.POST['stockName']
        quantity = request.POST['quantity']
        userId = request.user.id
        stockPrice = get_current_price(stockName)
        amount = calculate_amount(stockPrice, quantity)
        db.insert(userId=userId, stockName=stockName, quantity=quantity, amount=amount)
        buy_function(stockName)