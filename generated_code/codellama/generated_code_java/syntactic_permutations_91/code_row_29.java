import java.sql.*;
import java.util.Scanner;

public class Registration {
    public static void main(String[] args) throws Exception {
        Class.forName("com.mysql.jdbc.Driver");

        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/web_customer_tracker?" + "user=root&password=");

        Statement statement = connection.createStatement();

        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        int rowsInserted = statement.executeUpdate(
                "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')");
    }
}