import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Scanner;

import org.mindrot.jbcrypt.BCrypt;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, hashedPassword);

                int result = preparedStatement.executeUpdate();
                if (result > 0) {
                    System.out.println("Registration successful.");
                } else {
                    System.out.println("Registration failed.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        scanner.close();
    }
}
