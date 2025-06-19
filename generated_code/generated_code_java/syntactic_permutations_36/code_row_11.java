import java.sql.*;

public class Login {
    public static void main(String[] args) {
        String username = "username";
        String password = "password";
        if (checkDB(username, password)) {
            System.out.println("Successful login!");
        } else {
            System.out.println("Failed login!");
        }
    }
    
    public static boolean checkDB(String username, String password) throws SQLException {
        // Connect to database
        Connection connection = null;
        try {
            connection = DriverManager.getConnection("jdbc:mysql://localhost/database", "username", "password");
            
            // Prepare statement for querying the database
            String sql = "SELECT * FROM users WHERE username=? AND password=?";
            PreparedStatement stmt = connection.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, password);
            
            // Execute query
            ResultSet rs = stmt.executeQuery();
            
            if (rs.next()) {
                return true;
            } else {
                return false;
            }
        } catch (SQLException e) {
            System.out.println("Error connecting to database: " + e.getMessage());
            throw e;
        } finally {
            if (connection != null) {
                try {
                    connection.close();
                } catch (SQLException e) {
                    // Ignore this error
                    System.out.println(e);
                }
            }
        }
    }
}


### Explanation:
1. The first line imports the `java.sql.*` package, which contains classes for connecting to and interacting with databases in Java.
2. The next two lines define the username and password variables that will be used by the program.
3. The `main()` method is where the program starts executing. It calls the `checkDB()` method, passing in the username and password variables as arguments. If the method returns true, it prints "Successful login!" to the console. Otherwise, it prints "Failed login!".
4. The `checkDB()` method first sets up a connection to the database using the `DriverManager.getConnection()` method. It then creates a prepared statement for querying the database using the `connection.prepareStatement()` method. This method is used instead of creating a string and executing it as SQL, because it helps protect against SQL injection attacks.
5. The prepared statement is then executed using the `executeQuery()` method. The result set is stored in an object called `rs`. If there is a row in the database that matches both the username and password passed into the method, then the result set will have one row. If not, it will be empty.
6. Finally, the method returns true or false depending on whether the result set is non-empty. It also catches any SQL exceptions that occur and prints an error message to the console.