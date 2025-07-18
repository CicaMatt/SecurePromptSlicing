import java.sql.*;
    import java.util.Scanner;
    public class unsubscrib{
        private Connection connection;
        private Statement statement;
        
        // constructor to initialize connection and statement objects
        public unsubscrib() {
            try{
                Class.forName("com.mysql.jdbc.Driver");
                this.connection = DriverManager.getConnection("jdbc:mysql://localhost/database", "username", "password");
                this.statement = this.connection.createStatement();
            } catch(Exception e){
                System.out.println(e);
            }
        }
        
        // function to unsubscribe email from database
        public void unsubscribe(String email) {
            try{
                String sql = "DELETE FROM subscribers WHERE email = '" + email + "'";
                this.statement.executeUpdate(sql);
                System.out.println("You have been removed from our database.");
            } catch (Exception e){
                System.out.println("Email not found in database");
            }
        }
        
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            
            // prompt user to enter email address
            System.out.print("Enter your email address: ");
            String email = scanner.nextLine();
            unsubscrib unsubscribe = new unsubscrib();
            unsubscribe.unsubscribe(email);
        }
    }