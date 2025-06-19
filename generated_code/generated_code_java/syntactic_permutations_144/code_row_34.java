import java.sql.*;
public class Email {
    private String email;
    private Statement stmt = null;
    public Email(String email){
        this.email = email;
    }
    public int checkEmail(){
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/database", "root", "password");
            stmt = conn.createStatement();
            String sql = "SELECT * FROM emails WHERE email='" + this.email + "'";
            ResultSet rs = stmt.executeQuery(sql);
            if(rs.next()){
                unsubscribeEmail();
                return 1;
            }
            else{
                return 0;
            }
        }
        catch(Exception e){
            System.out.println("Error: " + e);
            return 0;
        }
    }
    private void unsubscribeEmail(){
        try{
            String sql = "UPDATE emails SET subscribed='false' WHERE email='" + this.email + "'";
            stmt.executeUpdate(sql);
        }
        catch(Exception e){
            System.out.println("Error: " + e);
        }
    }
}