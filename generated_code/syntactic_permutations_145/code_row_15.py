import requests

def buy_stock(stock_name, quantity):
  response = requests.get("https://api.iextrading.com/1.0/stock/" + stock_name + "/quote")
  data = response.json()
  price = data["latestPrice"]
  buy_function(price)

def buy_function(price):
  # Function to buy the stock
  pass