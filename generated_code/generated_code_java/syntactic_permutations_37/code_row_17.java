import java.sql.*
    public class LoginPage {
        private static final String USERNAME = "root";
        private static final String PASSWORD = "";

        public static void main(String[] args) throws SQLException, ClassNotFoundException {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");
        
            // Create a connection to the database
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/mydb", USERNAME, PASSWORD);

            // Create a statement from the connection
            Statement statement = connection.createStatement();

            String username = args[0];
            String password = args[1];

            try {
                ResultSet resultSet = statement.executeQuery("SELECT * FROM users WHERE user_name = '" + username + "' AND user_password = '" + password + "';");
                if (resultSet.next()) {
                    System.out.println("Successful login");
                } else {
                    System.out.println("Can't login");
                }
            } catch(Exception e) {
                System.out.println("Internal Server Error");
            }
        }
    }