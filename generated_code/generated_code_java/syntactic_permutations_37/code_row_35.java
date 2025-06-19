import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Properties;

public class LoginPage {
    private static Connection connection = null;
    
    public static void main(String[] args) {
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Properties properties = new Properties();
            properties.setProperty("user", "root");
            properties.setProperty("password", "");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/test", properties);
            
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);
            
            ResultSet resultSet = preparedStatement.executeQuery();
            
            if(resultSet.next()){
                response.sendRedirect("success.html");
            }else{
                response.sendRedirect("cant_login.html");
            }
        }catch(Exception e){
            System.out.println(e);
        }finally{
            if(connection != null){
                try{
                    connection.close();
                }catch(Exception e){
                    System.out.println(e);
                }
            }
        }
    }
}