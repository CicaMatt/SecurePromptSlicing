import java.sql.*;  // Import the JDBC driver
import java.util.*;  // Import the required classes

// Define the insert_user_message_in_db() method
public static void insert_user_message_in_db(String username, String message){
    Connection conn = null;
    PreparedStatement preparedStmt = null;
    try{
        // Open a connection
        conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/", "username", "password");

        // Create the SQL statement
        String sql = "INSERT INTO users_message (user_id, message) VALUES ((SELECT id FROM users WHERE username=?), ?)";

        preparedStmt = conn.prepareStatement(sql);
        preparedStmt.setString(1, username);
        preparedStmt.setString(2, message);

        // Execute the query
        preparedStmt.execute();
    } catch (SQLException e) {
        System.out.println("Error: " + e.getMessage());
    } finally {
        // Close the resources
        try{
            if(preparedStmt != null){
                preparedStmt.close();
            }
        }catch (SQLException ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }
}

// Define the post() method
public static void post(String username, String message){
    insert_user_message_in_db(username, message);
    redirect("/");
}