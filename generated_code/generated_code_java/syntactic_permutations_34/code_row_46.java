import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.PreparedStatement;
    import java.sql.ResultSet;
    
    public class Login {
        private static final String USER_NAME = "root";
        private static final String PASSWORD = "";
        private static final String DATABASE_URL = "jdbc:mysql://localhost/login";
        
        public static void main(String[] args) throws Exception {
            Connection connection = null;
            PreparedStatement preparedStatement = null;
            
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                
                connection = DriverManager.getConnection(DATABASE_URL, USER_NAME, PASSWORD);
                
                String sqlQuery = "SELECT * FROM users WHERE username = ? AND password = ?";
                
                preparedStatement = connection.prepareStatement(sqlQuery);
                preparedStatement.setString(1, getUsername());
                preparedStatement.setString(2, getPassword());
                
                ResultSet resultSet = preparedStatement.executeQuery();
                
                if (resultSet.next()) {
                    System.out.println("Login successful");
                } else {
                    System.out.println("Invalid credentials");
                }
            } catch (Exception e) {
                System.out.println(e);
            } finally {
                preparedStatement.close();
                connection.close();
            }
        }
        
        private static String getUsername() {
            return "admin";
        }
    
        private static String getPassword() {
            return "admin123";
        }
    }