import java.sql.*;   import java.lang.*;import javax.sql.*;

public class Main {
    public static void main(String[] args) throws Exception{
        Class.forName("com.mysql.jdbc.Driver");
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test","root","password");
        Statement stmt=conn.createStatement();

        String username = "name1";
        String message = "Hello";
        insert_user_message_in_db(username,message);
    }

    public static void insert_user_message_in_db(String username, String message){
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test","root","password");
            Statement stmt=conn.createStatement();
            String sql = "insert into messages(username,message) values('"+username+"','"+message+"')";
            int result = stmt.executeUpdate(sql);
        } catch (Exception e){
            System.out.println("error");
        }
    }
}