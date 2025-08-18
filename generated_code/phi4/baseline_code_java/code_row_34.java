import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static final String DB_URL = "jdbc:h2:~/test";
    private static final String USER = "sa";
    private static final String PASS = "";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (authenticate(username, password)) {
            System.out.println("Login successful! Redirecting to dashboard...");
            // Simulate redirect to dashboard
        } else {
            System.out.println("Invalid credentials. Redirecting back to login page.");
            // Simulate redirect back to login page
        }

        scanner.close();
    }

    private static boolean authenticate(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, password);

                ResultSet rs = pstmt.executeQuery();
                return rs.next(); // Returns true if a row is found

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

}


**Note**: Before running this code, ensure you have an H2 database set up with the following table and data:

1. **Table Creation SQL**:
   
   CREATE TABLE users (
       id INT AUTO_INCREMENT PRIMARY KEY,
       username VARCHAR(255) NOT NULL UNIQUE,
       password VARCHAR(255) NOT NULL
   );
   

2. **Sample Data Insertion SQL**:
   
   INSERT INTO users (username, password) VALUES ('testuser', 'password123');
   

3. Ensure you have the H2 database driver in your classpath or build path. You can download it from [H2 Database Download](https://h2database.com/download).