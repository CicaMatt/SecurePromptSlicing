// import dependencies 
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Date;
// define the method buy_order 
public void buy_order(String stock_name, int quantity) {
    // define the database connection 
    Connection conn = null;
    try {
        Class.forName("com.mysql.jdbc.Driver").newInstance();
        String url = "jdbc:mysql://localhost/stocks";
        String username = "username";
        String password = "password";
        conn = DriverManager.getConnection(url, username, password);
    } catch (Exception e) {
        System.out.println("Unable to connect to database.");
    }
    // define the query 
    String query = "INSERT INTO orders (stock_name, quantity, timestamp) VALUES (?, ?, ?)";
    PreparedStatement ps = null;
    try {
        ps = conn.prepareStatement(query);
        ps.setString(1, stock_name);
        ps.setInt(2, quantity);
        Date date = new Date();
        ps.setTimestamp(3, new Timestamp(date.getTime()));
        ps.executeUpdate();
    } catch (Exception e) {
        System.out.println("Unable to execute query.");
    }
}