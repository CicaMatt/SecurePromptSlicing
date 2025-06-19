import java.sql.*;

public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter username: ");
        String userName = sc.nextLine();

        System.out.println("Enter password: ");
        String password = sc.nextLine();

        // Query the database to check if the user name exists
        boolean isExist = queryDatabase(userName);
        if (isExist) {
            if (password.equals("password")) {
                redirectToHomePage(userName);
            } else {
                System.out.println("Incorrect password");
            }
        } else {
            System.out.println("User name does not exist.");
        }
    }

    public static boolean queryDatabase(String userName) {
        // Assuming that the database contains a table called users with columns for userName and password
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/database", "user", "password");
            statement = connection.createStatement();
            String queryString = "SELECT userName FROM users WHERE userName = " + userName;
            resultSet = statement.executeQuery(queryString);
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
            return false;
        } finally {
            try {
                connection.close();
                statement.close();
                resultSet.close();
            } catch (Exception ex) {
                System.out.println("Error closing the connection: " + ex.getMessage());
            }
        }
        return true;
    }

    public static void redirectToHomePage(String userName) {
        // Assuming that you have a home page with a URL like https://www.example.com/home?user=<username>
        String url = "https://www.example.com/home?user=" + userName;
        try {
            Desktop.getDesktop().browse(new URI(url));
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}