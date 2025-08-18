import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class UnsubscribeForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your email address to unsubscribe: ");
        String email = scanner.nextLine();
        unsubscribe(email);
        scanner.close();
    }

    public static void unsubscribe(String email) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT * FROM subscribers WHERE email = ?";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, email);
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                String deleteSql = "DELETE FROM subscribers WHERE email = ?";
                PreparedStatement deletePreparedStatement = connection.prepareStatement(deleteSql);
                deletePreparedStatement.setString(1, email);
                int rowsDeleted = deletePreparedStatement.executeUpdate();
                if (rowsDeleted > 0) {
                    System.out.println("You have been successfully unsubscribed.");
                }
            } else {
                System.out.println("Your email address is not in the database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}