import java.util.*;
import java.sql.*;

public class Stock {
    private String name;
    private int quantity = 0;
    
    public void setName(String name) {
        this.name = name;
    }
    
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }
    
    public String getName() {
        return name;
    }
    
    public int getQuantity() {
        return quantity;
    }
}


### Explanation:
This code defines a Stock class with two fields, one for the stock name and one for the quantity. The class also has two methods to set the value of each field and two methods to retrieve the values of each field.