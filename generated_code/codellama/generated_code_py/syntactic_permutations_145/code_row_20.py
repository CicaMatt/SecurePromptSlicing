def insert_stock(self,name,quantity):
        cursor.execute("""INSERT INTO stocks (name, quantity) VALUES (%s,%s)""",(name,quantity))



    #your code here