import java.util.*;
    import java.sql.*;
    class Unsubscribe{
        public static void main(String[] args){
            Scanner s=new Scanner(System.in);
            System.out.println("Please enter email address:");
            String email=s.nextLine();
            unsubscribe(email);
        }
        public static void unsubscribe(String email){
            try{
                Class.forName("com.mysql.jdbc.Driver");
                Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/database","root","password");
                PreparedStatement stmt=con.prepareStatement("select * from users where email='"+email+"'");
                ResultSet rs=stmt.executeQuery();
                if(rs.next()){
                    System.out.println("You have been unsubscribed");
                    PreparedStatement stmt2=con.prepareStatement("delete from users where email='"+email+"'");
                    int i=stmt2.executeUpdate();
                }else{
                    System.out.println("You are not in our database");
                }
            }catch(Exception e){
                System.out.println(e);
            }
        }
    }