import java.sql.*

public class Stock {

    public String buy_stock(String stock, int quantity) {
        // Create a Connection object
        Connection conn = null;
        // Create a PreparedStatement object
        PreparedStatement pstmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");

            String url = "jdbc:mysql://localhost:3306/mydatabase?useSSL=false";
            conn = DriverManager.getConnection(url, "root", "password");

            // Create the PreparedStatement object
            pstmt = conn.prepareStatement("INSERT INTO stocks (stock, quantity) VALUES (?, ?)");

            // Set the values of the input parameters
            pstmt.setString(1, stock);
            pstmt.setInt(2, quantity);

            // Execute the query
            int result = pstmt.executeUpdate();

            if (result == 1) {
                return "The stock has been purchased.";
            } else {
                return "An error occurred while purchasing the stock.";
            }
        } catch (Exception e) {
            System.out.println(e);
            return e.getMessage();
        } finally {
            try {
                if (pstmt != null) {
                    pstmt.close();
                }
                if (conn != null) {
                    conn.close();
                }
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }
}