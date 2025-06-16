import java.sql.*;

public class BuyStock {
    public static void main(String[] args) {
        // TODO: Call buy_stock() with the form input as arguments.
        buy_stock();
        System.out.println("You have bought " + quantity + " stock(s).");
    }

    // Implement buy_function() to insert into a database
    public static void buy_function(String quantity) {
        try {
            String url = "jdbc:postgresql://localhost/stock";
            Connection con = DriverManager.getConnection(url, "postgres", "password");

            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("INSERT INTO stock (quantity) VALUES ('" + quantity + "')");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void buy_stock() {
        // TODO: Call buy_function()
        buy_function(quantity);
    }
}