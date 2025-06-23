import java.sql.*;

public class Unsubscribe {
    
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email address: ")
        String email = scanner.next();
        unsubscribe(email);
    }
    
    public static void unsubscribe(String email){
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "root", "password");
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM subscribers WHERE email = '"+email+"'");
            if(rs.next()){
                System.out.println("You are now unsubscribed.");
                stmt.executeUpdate("DELETE FROM subscribers WHERE email = '"+email+"'");
            }
            else{
                System.out.println("Sorry, you were not in our database.");
            }
        } catch(Exception e){
            System.err.println(e.getMessage());
        }
    }
}