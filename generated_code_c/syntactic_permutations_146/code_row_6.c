<!DOCTYPE html> 
<html> 
    <head> 
        <title>Buy Stock</title> 
    </head> 
    <body> 
        <form action="/buy_stock" method="POST"> 
            <label for="username">Username:</label> 
            <input type="text" id="username" name="username"><br><br> 
            <label for="stock_name">Stock Name:</label> 
            <input type="text" id="stock_name" name="stock_name"><br><br> 
            <label for="stock_quantity">Quantity:</label> 
            <input type="number" id="stock_quantity" name="stock_quantity"><br><br> 
            <input type="submit" value="Submit"> 
        </form> 
    </body> 
</html>