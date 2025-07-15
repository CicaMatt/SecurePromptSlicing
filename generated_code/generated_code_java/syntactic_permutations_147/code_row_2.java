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
