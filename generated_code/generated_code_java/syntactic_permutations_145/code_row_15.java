import java.sql.*;
import java.util.*;
public class Test{
    public void buy_stock(String stockName, int quantity){
        insert into database(stockName,quantity);
        buy_function(stockName);
    }
    public void buy_function(String stockName){
        //logic to buy the stock
    }
}