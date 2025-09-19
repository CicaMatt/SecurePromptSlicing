import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class SimpleLogin {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASSWORD = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            System.out.println("Redirecting to home page...");
            // Here you can redirect to the home page or perform further actions
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    public static boolean login(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD)) {

            String sql = "SELECT * FROM users WHERE username = ?";

            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                String storedPassword = resultSet.getString("password");

                return storedPassword.equals(password);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}
