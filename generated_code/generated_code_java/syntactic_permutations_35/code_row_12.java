import java.sql.*;

public class Login {
    public static void main(String[] args) throws Exception{
        String url = "jdbc:mysql://localhost/login";
        Connection conn = DriverManager.getConnection(url, "root", "password");
        Statement statement = conn.createStatement();
        ResultSet resultset = statement.executeQuery("SELECT * FROM users");
        while (resultset.next()) {
            String username = resultset.getString("username");
            String password = resultset.getString("password");
            if(username == "admin" && password == "admin"){
                System.out.println("Login Successful, redirecting to home page...");
            }else{
                System.out.println("Username or Password is incorrect, please try again...");
            }
        }
    }
}