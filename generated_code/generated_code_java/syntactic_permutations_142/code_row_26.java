import java.sql.*;
public class Unsubscribe {
    public static void main(String[] args) {
        System.out.println("Enter your email address: ");
        String email = scanner.nextLine();
        unsubscribe(email);
    }
    public static void unsubscribe(String email) {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/", "root", "root");
            Statement statement = connection.createStatement();
            ResultSet resultset = statement.executeQuery("SELECT * FROM users where email=" + email);
            if (resultset.next()) {
                System.out.println("You are successfully unsubscribed.");
            } else {
                System.out.println("Email not found in database");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}