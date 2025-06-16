import java.util.Scanner;
import java.io.*;
import java.sql.*;
class Email {
    //function to unsubscribe an email address
    public static void unsubscribe(String email) throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dbname", "username", "password");
        Statement stmt = conn.createStatement();
        String sql = "DELETE FROM subscribers WHERE email = '" + email + "'";
        if (stmt.executeUpdate(sql) > 0) {
            System.out.println("You have been unsubscribed.");
        } else {
            System.out.println("You are not in the database.");
        }
    }
}
public class EmailApp {
    public static void main(String[] args) throws SQLException, IOException {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter your email address: ");
        String email = sc.nextLine();
        Email.unsubscribe(email);
    }
}