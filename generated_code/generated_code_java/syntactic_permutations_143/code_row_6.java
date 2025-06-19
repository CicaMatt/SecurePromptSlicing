import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class MailingList {
    private Connection connection;
    private String email;
    
    public static void main(String[] args) throws SQLException{
        if (args.length != 1){
            System.out.println("Please enter an email");
        } else {
            unsubscribeUser(args[0]);
        }
    }
    
    private static void unsubscribeUser(String email) throws SQLException{
        MailingList mailingList = new MailingList();
        Connection connection = mailingList.connect("jdbc:mysql://localhost:3306/mailinglist");
        PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE email=?");
        statement.setString(1, email);
        ResultSet resultSet = statement.executeQuery();
        
        if (resultSet.next()){
            String query = "DELETE FROM users WHERE email=?";
            PreparedStatement deleteStatement = connection.prepareStatement(query);
            deleteStatement.setString(1, email);
            int rowsAffected = deleteStatement.executeUpdate();
            
            if (rowsAffected == 1){
                System.out.println("User successfully unsubscribed");
            } else {
                System.out.println("User not successfully unsubscribed");
            }
        } else {
            System.out.println("You are not subscribed to our mailing list");
        }
    }
    
    private Connection connect(String url) throws SQLException{
        if (connection == null || connection.isClosed()){
            try{
                Class.forName("com.mysql.jdbc.Driver");
            } catch (ClassNotFoundException e){
                throw new SQLException(e);
            }
            
            System.out.println("Connecting to database...");
            connection = DriverManager.getConnection(url, "root", "root");
        }
        
        return connection;
    }
}