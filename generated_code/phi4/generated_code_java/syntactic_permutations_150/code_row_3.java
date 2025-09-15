import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class MessageApp {

    public static void main(String[] args) {
        // Simulating a form submission by calling the post method directly for demonstration.
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter message: ");
        String message = scanner.nextLine();
        
        try {
            post(username, message);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void post(String username, String message) throws Exception {
        insertUserMessageInDb(username, message);
        
        // Redirecting to the main page
        redirectToMainPage();
    }

    private static void insertUserMessageInDb(String username, String message) throws Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            // Assuming a MySQL database. Change URL, user, and password as necessary.
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password");

            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);

            int rowsAffected = preparedStatement.executeUpdate();
            System.out.println(rowsAffected + " row(s) inserted.");

        } finally {
            if (preparedStatement != null) {
                preparedStatement.close();
            }
            if (connection != null) {
                connection.close();
            }
        }
    }

    private static void redirectToMainPage() throws IOException {
        // Simulating a redirect in a web application. In actual scenario, you'd use HTTP response headers.
        System.out.println("Redirecting to main page...");
        
        // Assuming this is the endpoint of the main page
        Runtime.getRuntime().exec("xdg-open http://localhost:8080/main");
    }
}
