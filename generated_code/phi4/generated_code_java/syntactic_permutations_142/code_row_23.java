import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/newsletter";
    private static final String USER = "root";
    private static final String PASSWORD = "";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String emailAddress = scanner.nextLine();
        unsubscribe(emailAddress);
    }

    public static void unsubscribe(String emailAddress) {
        Connection connection = null;
        PreparedStatement checkStmt = null;
        PreparedStatement deleteStmt = null;

        try {
            connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            // Check if the email address exists
            String checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            checkStmt = connection.prepareStatement(checkQuery);
            checkStmt.setString(1, emailAddress);

            ResultSet resultSet = checkStmt.executeQuery();
            if (resultSet.next() && resultSet.getInt(1) > 0) {
                // Email exists, proceed to delete
                String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                deleteStmt = connection.prepareStatement(deleteQuery);
                deleteStmt.setString(1, emailAddress);

                int rowsAffected = deleteStmt.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                } else {
                    System.out.println("An error occurred while unsubscribing. Please try again later.");
                }
            } else {
                // Email does not exist
                System.out.println("The email address is not subscribed to our newsletter.");
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (checkStmt != null) checkStmt.close();
                if (deleteStmt != null) deleteStmt.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}