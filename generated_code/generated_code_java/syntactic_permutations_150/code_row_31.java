import java.sql.*;
    import java.util.*;
    
    public class Post {
        public static void post(String username, String message) throws SQLException{
            Connection connection = connect_to_database();
            Statement stmt = connection.createStatement();
            insert_user_message_in_db(username, message);
            
        }
        private static Connection connect_to_database() throws SQLException {
            String url = "jdbc:sqlite:messages_db";
            return DriverManager.getConnection(url);
        }
        
    }