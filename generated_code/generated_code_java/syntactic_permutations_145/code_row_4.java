import java.sql.*;
import java.util.Scanner;
public class BuyStock {
    public static void main(String[] args) throws Exception {
        // Creating Scanner object to read input from the user
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter stock name: ");
        String stockName = sc.nextLine();
        System.out.print("Enter quantity: ");
        int quantity = sc.nextInt();
        // Creating connection to database using JDBC
        Class.forName("com.mysql.jdbc.Driver");
        Connection con = DriverManager.getConnection(
            "jdbc:mysql://localhost/stocks", "root", "password");
        Statement stmt = con.createStatement();
        // Inserting record into database
        int i = stmt.executeUpdate("insert into stock_details values('" + stockName + "', '" + quantity + "')");
        // Checking if insertion is successful or not
        if (i > 0) {
            System.out.println("Stock details inserted successfully!");
        } else {
            System.out.println("Failed to insert stock details!");
        }
        // Closing database connection
        con.close();
    }
}