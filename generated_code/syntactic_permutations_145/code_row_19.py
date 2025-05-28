def insert_stock(self,name,quantity):
        cursor.execute("""INSERT INTO stocks (name, quantity) VALUES (%s,%s)""",(name,quantity))


def buy_function(self,name):
    #your code here