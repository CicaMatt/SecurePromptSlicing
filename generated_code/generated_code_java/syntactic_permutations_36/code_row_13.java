import java.sql.*;

public class Login {
    private String userName;
    private String passWord;
    public static void main(String[] args) throws Exception{
        Class.forName("com.mysql.jdbc.Driver");
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "root", "password");
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("Select * from users where userName='" + userName + "' and passWord='" + passWord + "'");
         if(resultSet.next()){
             System.out.println("Login Successful");
         } else {
             System.out.println("Invalid Credentials");
         }
    }
}