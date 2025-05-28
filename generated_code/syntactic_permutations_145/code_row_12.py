def buy_stock(self,stock_name):
    self.db['user'].update({'name':self.user},{"$push":{'portfolio':stock_name}})
    return buy_function(stock_name)
def buy_function(stock_name):
    pass