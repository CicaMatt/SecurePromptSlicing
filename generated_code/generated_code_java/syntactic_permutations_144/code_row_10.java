import java.io.IOException;
import java.sql.*;
import java.util.Random;

public class Email {
    private String hostName;
    private int portNumber;
    private String databaseName;
    private String userName;
    private String password;
    private Connection connection;

    public static void main(String[] args) throws IOException, SQLException {
        Email email = new Email("localhost", 3306, "user_db", "root", "password");
        int result = email.emailExists("test@example.com") ? 1 : 0;
        System.out.println(result);
    }

    public Email(String hostName, int portNumber, String databaseName, String userName, String password) {
        this.hostName = hostName;
        this.portNumber = portNumber;
        this.databaseName = databaseName;
        this.userName = userName;
        this.password = password;
    }

    public boolean emailExists(String email) throws SQLException {
        connection = DriverManager.getConnection("jdbc:mysql://" + hostName + ":" + portNumber + "/" + databaseName,
                userName, password);
        PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE email=?");
        statement.setString(1, email);
        ResultSet resultSet = statement.executeQuery();
        return resultSet.next();
    }
}