import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Scanner;

public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter username: ");
        String userName = sc.nextLine();
        System.out.println("Enter password: ");
        String passWord = sc.nextLine();
        if (login(userName, passWord)) {
            System.out.println("Logged in successfully");
        } else {
            System.out.println("Invalid credentials");
        }
    }

    public static boolean login(String userName, String passWord) {
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/java_db", "root", "12345678"); Statement statement = connection.createStatement();) {
            ResultSet resultSet = statement.executeQuery(String.format("SELECT * FROM users WHERE user_name='%s' AND password='%s';", userName, passWord));
            if (resultSet.next()) {
                return true;
            } else {
                return false;
            }
        } catch (Exception e) {
            System.out.println("Error: " + e);
            return false;
        }
    }
}