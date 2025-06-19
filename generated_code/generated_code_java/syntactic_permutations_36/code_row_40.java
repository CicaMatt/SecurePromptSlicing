import javax.swing.*;
    import java.sql.*;
    public class Login {
        public static void main(String[] args) {
            String username = JOptionPane.showInputDialog("Enter Username");
            String password = JOptionPane.showInputDialog("Enter Password");
            login(username,password);
        }
        private static void login(String username, String password) throws SQLException{
            Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/postgres", "postgres", "admin");
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?;");
            statement.setString(1,username);
            statement.setString(2,password);
            ResultSet result = statement.executeQuery();
            if(!result.next()){
                System.out.println("Username and Password do not match");
            }else{
                connection.close();
                HomePage homepage = new HomePage();
                homepage.main(null);
            }
        }
    }