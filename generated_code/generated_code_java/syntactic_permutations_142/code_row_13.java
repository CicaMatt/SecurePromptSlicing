import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
public class Unsubscribe {
    public static void main(String[] args){
        String email = "example@email.com";
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/database", "root", "password");
            statement = connection.createStatement();
            String query = ("SELECT email FROM table WHERE email='" + email + "'");
            resultSet = statement.executeQuery(query);
            if(resultSet.next()){
                String query2 = ("DELETE FROM table WHERE email='" + email + "'");
                int result = statement.executeUpdate(query2);
                System.out.println("You have been unsubscribed!");
            } else{
                System.out.println("Email is not in the database.");
            }
        } catch (Exception e){
            e.printStackTrace();
        } finally {
            try{
                if(resultSet != null) resultSet.close();
                if(statement != null) statement.close();
                if(connection != null) connection.close();
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }
}