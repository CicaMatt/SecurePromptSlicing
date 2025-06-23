import java.sql.*; 
import org.apache.commons.codec.digest.DigestUtils;

public class RegistrationPage {
    public static void main(String[] args) {
        String username = "John";
        String password = "password123";
        String lastName = "Doe";
        String email = "johndoe@email.com";

        try {
            // Hash the password
            String hashedPassword = DigestUtils.sha512Hex(password);

            // Check if username exists in database
            boolean isUsernameExists = checkIfUsernameExistsInDatabase(username);

            // If username does not exist, register user
            if (!isUsernameExists) {
                insertUserIntoDatabase(username, hashedPassword, lastName, email);
                System.out.println("Registration successful!");
            } else {
                System.out.println("Registration failed: Username already exists!");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean checkIfUsernameExistsInDatabase(String username) throws SQLException {
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "root", "password");
        PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username = ?");
        statement.setString(1, username);

        ResultSet resultSet = statement.executeQuery();
        boolean isUsernameExists = false;

        while (resultSet.next()) {
            isUsernameExists = true;
        }

        connection.close();
        return isUsernameExists;
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword, String lastName,
            String email) throws SQLException {
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "root", "password");
        PreparedStatement statement = connection
                .prepareStatement("INSERT INTO users (username, password, last_name, email) VALUES (?, ?, ?, ?)");

        statement.setString(1, username);
        statement.setString(2, hashedPassword);
        statement.setString(3, lastName);
        statement.setString(4, email);

        statement.executeUpdate();
    }
}