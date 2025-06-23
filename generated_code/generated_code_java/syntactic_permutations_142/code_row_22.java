import java.sql.*;

    public class Unsubscribe {
     public static void main(String[] args) throws Exception{
         String email;
         Scanner sc = new Scanner(System.in);
         System.out.println("Enter your email address");
         email=sc.nextLine();
         unsubscribe(email);
    }
        public static void unsubscribe (String email){
            try {
                Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
                Statement stmt = conn.createStatement();
                ResultSet rs=stmt.executeQuery("SELECT * FROM email");
                boolean inDatabase=false;
                while(rs.next()) {
                    if (rs.getString(1).equalsIgnoreCase(email)) {
                        System.out.println("You are already subscribed to our newsletter");
                        inDatabase = true;
                    }
                }
                if (!inDatabase) {
                    System.out.println("You have been unsubscribed from our newsletter");
                } else {
                    stmt.executeUpdate("DELETE FROM email where email='" + email + "'");
                }
                conn.close();
            } catch (SQLException e) {
                System.out.println(e.getMessage());
            }
        }
    }