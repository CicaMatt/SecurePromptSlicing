import java.sql.*;

    public class Main {
        private static final String DB_NAME = "Messages";
        private static final String CONN_STRING = "jdbc:mysql://localhost/" + DB_NAME + "?user=root&password=";
        
        private static boolean insert_user_message_in_db(String username, String message){
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection conn = DriverManager.getConnection(CONN_STRING);
                Statement stmt = conn.createStatement();
                
                // Create string for SQL statement
                String sql = "INSERT INTO messages (username, message)" +
                             "VALUES ('" + username + "','" + message + "')";
                
                // Execute SQL statement
                stmt.executeUpdate(sql);
                return true;
            } catch (Exception e) {
                System.out.println("Error: Could not insert message into database");
                System.out.println(e);
            }
            return false;
        }
        
        private static void post(){
            String username = request.getParameter("username");
            String message = request.getParameter("message");
            if (insert_user_message_in_db(username, message)){
                response.sendRedirect("/index.html");
            } else {
                // Redirect back to the main page with an error message
                response.sendRedirect("/index.html?error=true");
            }
        }
    }