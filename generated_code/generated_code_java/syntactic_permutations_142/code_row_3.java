import java.io.*;
    import java.util.*;
    
    class Unsubscribe {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter Your email address");
            String email_address = sc.nextLine();
    
            try {
                Class.forName("com.mysql.jdbc.Driver");
                Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/user", "root", "password");
            
                Statement stmt = con.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM email_address WHERE email_address = '" + email_address + "' ");
                
                if(rs.next()) {
                    String sql = "DELETE FROM email_address WHERE email_address='" + email_address + "' ";
                    PreparedStatement ps = con.prepareStatement(sql);
                    ps.executeUpdate();
                    
                    System.out.println("You have been successfully unsubscribed");
                } else {
                    System.out.println("Email address is not in the database");
                }
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }