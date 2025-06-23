import java.security.MessageDigest; 
   import java.sql.*;
    public class DatabaseConnection{
       private static final String DB_URL = "jdbc:mysql://localhost/java_db";
       private static final String USERNAME = "root";
       private static final String PASSWORD = "password";
       
       public static void main(String[] args) {
           try{
               Connection conn = DriverManager.getConnection(DB_URL,USERNAME,PASSWORD);
               Statement stmt = conn.createStatement();
               
               Scanner in = new Scanner(System.in);
               System.out.print("Enter username: ");
               String username = in.nextLine();
               System.out.print("Enter password: ");
               String password = in.nextLine();
               
               // hash the password using SHA-256 algorithm
               MessageDigest md = MessageDigest.getInstance("SHA-256");
               md.update(password.getBytes());
               byte[] digest = md.digest();
               String hashedPassword = new String(digest, StandardCharsets.UTF_8);
               
               // insert username and password into the database
               stmt.executeUpdate("insert into users (username, password) values ('" + username + "', '" + hashedPassword + "')");
           }catch(Exception e){
               System.out.println(e.getMessage());
           }
       }
    }