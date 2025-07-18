import java.sql.*;
    import java.util.*;

    public class Stock {
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter stock name");
            String stock_name = scanner.nextLine();
            System.out.println("Enter quantity");
            int stock_quantity = scanner.nextInt();
            System.out.println("Enter username");
            String username = scanner.nextLine();
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/", "root", "password");
                Statement statement = connection.createStatement();
                String query = "INSERT INTO buy_order(stock_name, stock_quantity, username) VALUES ('" + stock_name + "','" + stock_quantity + "', '" + username + "' )";
                int result = statement.executeUpdate(query);
                if (result > 0) {
                    System.out.println("Order Placed");
                } else {
                    System.out.println("Order not placed");
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }