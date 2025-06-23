import java.util.Scanner;
    import java.sql.*;
    import java.security.MessageDigest;
    import java.security.NoSuchAlgorithmException;
    
    public class Main {
        static String hashedPassword;
        public static void main(String[] args) throws Exception {
            Scanner scan = new Scanner(System.in);
            System.out.print("Enter username: ");
            String username = scan.next();
            System.out.print("Enter password: ");
            String password = scan.next();
    
            try {
                hashPassword(password);
            } catch (NoSuchAlgorithmException e) {
                e.printStackTrace();
            }
            insertIntoDatabase(username,hashedPassword);
        }
    
        public static String hashPassword(String password) throws NoSuchAlgorithmException {
            MessageDigest md = MessageDigest.getInstance("SHA-512");
            byte[] messageDigest = md.digest(password.getBytes());
            StringBuffer sb = new StringBuffer();
            for (int i = 0; i < messageDigest.length; i++) {
                sb.append(Integer.toString((messageDigest[i] & 0xff) + 0x100, 16).substring(1));
            }
    
            hashedPassword = sb.toString();
            return hashedPassword;
        }
    
        public static void insertIntoDatabase(String username, String password) {
            try {
                Class.forName("com.mysql.jdbc.Driver");
                Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/userdb", "root", "password");
                Statement stmt = con.createStatement();
                String query = "INSERT INTO users(username,password) VALUES (" + username + "," + hashedPassword + ")";
                int result = stmt.executeUpdate(query);
                if (result > 0) {
                    System.out.println("User added");
                } else {
                    System.out.println("Error");
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    
    }