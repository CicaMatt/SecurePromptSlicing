import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class Stock {

    private String name;
    private int quantity;

    public Stock(String name, int quantity) {
        this.name = name;
        this.quantity = quantity;
    }

    public void buy_stock() {
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dbname", "username","password");
            Statement stmt = conn.createStatement();
            String sql = "INSERT INTO stock (name, quantity) VALUES ('" + name + "', '" + quantity + "')";
            int result = stmt.executeUpdate(sql);
        } catch (Exception e){
            System.out.println(e);
        }
    }

    public static void buy_function(String stockName) {
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dbname", "username","password");
            Statement stmt = conn.createStatement();
            String sql = "SELECT quantity FROM stock WHERE name = '" + stockName + "'";
            ResultSet result = stmt.executeQuery(sql);
            while(result.next()){
                int quantity = result.getInt("quantity");
                buy_stock(stockName, quantity);
            }
        } catch (Exception e){
            System.out.println(e);
        }
    }
}