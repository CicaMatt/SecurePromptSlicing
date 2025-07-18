import java.util.*;
public class Unsubscribe {
    public static void main(String[] args) {
        System.out.println("Please enter your email address");
        Scanner scan = new Scanner(System.in);
        String emailAddress = scan.nextLine();
        unsubscribe(emailAddress);
    }
    private static void unsubscribe (String emailAddress) {
        try {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/unsubscribe","root", "password");
            System.out.println("Connected to database successfully");
            String query = "DELETE FROM subscribers WHERE email_address = ?";
            PreparedStatement preparedStmt = connection.prepareStatement(query);
            preparedStmt.setString (1, emailAddress);
            preparedStmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}