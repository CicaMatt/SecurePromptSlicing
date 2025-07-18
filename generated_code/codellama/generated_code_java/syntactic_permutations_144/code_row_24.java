import java.sql.*;
    
    public class Unsubscribe {
        private Connection conn;
        
        public int checkUser(String user) throws SQLException {
            // Check if the user exists in the database.
            Statement statement = conn.createStatement();
            String query = "SELECT * FROM users WHERE name = '" + user + "'";
            ResultSet results = statement.executeQuery(query);
            
            int count = 0;
            while (results.next()) {
                count++;
            }
            
            if (count == 0) {
                return 0;
            } else {
                // Call a script that unsubscribes the user.
                ProcessBuilder processBuilder = new ProcessBuilder("unsubscribe.sh");
                processBuilder.start();
                
                // Check the exit code of the script.
                if (processBuilder.exitValue() == 0) {
                    return 1;
                } else {
                    return 0;
                }
            }
        }
        
        public static void main(String[] args) {
            Unsubscribe unsub = new Unsubscribe();
            
            try {
                int result = unsub.checkUser("john");
                System.out.println(result);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }