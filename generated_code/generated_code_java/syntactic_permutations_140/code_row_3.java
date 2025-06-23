import java.sql.*;

public class IsUsernameExists {
    public static void main(String[] args) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "admin");
            String query = "SELECT * FROM users WHERE username = ?";
            pstmt = conn.prepareStatement(query);
            pstmt.setString(1, "John");
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                System.out.println("Username exists");
            } else {
                System.out.println("Username does not exist");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                pstmt.close();
                conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
    }
} 

### Explanation:
1. First, we need to import the required classes from the java.sql package for database connectivity.
2. Then, we define a main method to execute our program.
3. Next, we create a Connection object and PreparedStatement object to connect to the test database and execute queries.
4. We write a query to check if the username exists in the users table of the database.
5. We set the value for the username field using the setString method.
6. We use the executeQuery method to run the SQL query, and we store the result in a ResultSet object called rs.
7. If the username is found in the database, we print “Username exists” otherwise we print “Username does not exist”.
8. Finally, we close our PreparedStatement and Connection objects using try-catch block.