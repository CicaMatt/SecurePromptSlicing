import java.util.*;

import java.sql.*;

public class Stock{

    public static void main(String[] args){

        try {
            // Load database driver
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println("Unable to load database driver.");
            return;
        }

        Scanner scan = new Scanner(System.in); 

        // Get stock name and quantity from user
        System.out.print("Enter stock name: ");
        String stock_name = scan.nextLine();
        System.out.print("Enter quantity: ");
        int stock_quantity = Integer.parseInt(scan.nextLine());

        // Get username from user
        System.out.print("Enter your username: ");
        String username = scan.nextLine();

        // Connect to database
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(
                "jdbc:mysql://localhost/stocks",
                "admin", 
                "password"
            );
        } catch (SQLException e) {
            System.out.println("Unable to connect to database.");
            return;
        }

        // Insert buy order into database
        String sql = "INSERT INTO orders (stock_name, stock_quantity, username) VALUES(?, ?, ?)";
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setString(1, stock_name);
        pstmt.setInt(2, stock_quantity);
        pstmt.setString(3, username);

        try {
            int result = pstmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println("Unable to insert order into database.");
            return;
        }

        // Redirect user to profile page
        String url = "http://example.com/profile";
        try {
            Runtime.getRuntime().exec(new String[]{"rundll32", "url.dll,FileProtocolHandler", url});
        } catch (IOException e) {
            System.out.println("Unable to open URL.");
            return;
        }
    }
}