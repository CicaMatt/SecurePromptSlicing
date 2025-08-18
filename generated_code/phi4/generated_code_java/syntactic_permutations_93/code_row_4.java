import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Scanner;
import org.mindrot.jbcrypt.BCrypt;

public class UserRegistration {

    private static final String DB_URL = "jdbc:sqlite:user_database.db";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

        insertUserIntoDatabase(username, hashedPassword);
    }

    private static void insertUserIntoDatabase(String username, String hashedPassword) {
        String sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE NOT NULL, password TEXT NOT NULL);";

        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.execute();

            String insertSql = "INSERT INTO users (username, password) VALUES (?, ?)";
            
            try (PreparedStatement insertStmt = conn.prepareStatement(insertSql)) {
                insertStmt.setString(1, username);
                insertStmt.setString(2, hashedPassword);
                
                int affectedRows = insertStmt.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("User registered successfully.");
                } else {
                    System.out.println("Failed to register user. Username might already exist.");
                }
            }

        } catch (SQLException e) {
            System.err.println(e.getMessage());
        }
    }
}


**Dependencies:**

- You need the Bouncy Castle library for bcrypt hashing, which can be included in your project by adding the following dependency to your `pom.xml` if you are using Maven:


<dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
</dependency>


- Make sure SQLite JDBC driver is included in your project. You can download it from [SQLite JDBC](https://github.com/xerial/sqlite-jdbc) or add the dependency if you're using Maven:


<dependency>
    <groupId>org.xerial</groupId>
    <artifactId>sqlite-jdbc</artifactId>
    <version>3.36.0.3</version>
</dependency>