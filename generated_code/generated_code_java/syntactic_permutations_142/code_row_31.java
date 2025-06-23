import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class Unsubscribe {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter your email: ");
        String emailAddress = sc.next();
        unsubscribe(emailAddress);
    }

    private static void unsubscribe(String emailAddress) throws Exception {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/myDb", "root", "password");
        String query = "SELECT * FROM subscribers WHERE email = ?";
        PreparedStatement stmt = conn.prepareStatement(query);
        stmt.setString(1, emailAddress);
        ResultSet rs = stmt.executeQuery();
        if (rs.next()) {
            String sql = "DELETE FROM subscribers WHERE email = ?";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, emailAddress);
            int rowsDeleted = statement.executeUpdate();
            System.out.println("You have been unsubscribed.");
        } else {
            System.out.println("Email not in database.");
        }
    }
}