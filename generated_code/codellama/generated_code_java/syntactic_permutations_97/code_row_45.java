import java.sql.*;
    import java.security.MessageDigest;
    import java.util.Scanner;

    public class Registration {
        private static Scanner sc;
    
        public static void main(String[] args) throws Exception {
            sc = new Scanner(System.in);
        
            System.out.print("Username: ");
            String username = sc.nextLine();
        
            System.out.print("Password: ");
            String password = sc.nextLine();
        
            System.out.print("First name: ");
            String firstName = sc.nextLine();
        
            System.out.print("Last name: ");
            String lastName = sc.nextLine();
            
            System.out.print("Email: ");
            String email = sc.nextLine();
        
            String hashedPassword = getSHA1(password);
    
            if (usernameExists(username)) {
                System.out.println("Username already exists!");
            } else {
                registerUser(username, hashedPassword, firstName, lastName, email);
                System.out.println("Registration successful");
            }
        }
    
        private static boolean usernameExists(String username) throws Exception {
            Connection conn = null;
        
            try {
                Class.forName("com.mysql.jdbc.Driver").newInstance();
                conn = DriverManager.getConnection("jdbc:mysql://localhost/user", "root", "root");
            
                String sql = "SELECT * FROM users WHERE username=?";
                PreparedStatement stmt = conn.prepareStatement(sql);
                stmt.setString(1, username);
            
                ResultSet rs = stmt.executeQuery();
            
                return rs.next();
            } finally {
                if (conn != null) {
                    try { conn.close(); } catch (SQLException e) {}
                }
            }
        }
    
        private static void registerUser(String username, String password, String firstName, String lastName, String email) throws Exception {
            Connection conn = null;
        
            try {
                Class.forName("com.mysql.jdbc.Driver").newInstance();
                conn = DriverManager.getConnection("jdbc:mysql://localhost/user", "root", "root");
            
                String sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
                PreparedStatement stmt = conn.prepareStatement(sql);
                stmt.setString(1, username);
                stmt.setString(2, password);
                stmt.setString(3, firstName);
                stmt.setString(4, lastName);
                stmt.setString(5, email);
            
                int rowsUpdated = stmt.executeUpdate();
            } finally {
                if (conn != null) {
                    try { conn.close(); } catch (SQLException e) {}
                }
            }
        }
    
        private static String getSHA1(String input) throws Exception {
            MessageDigest md = MessageDigest.getInstance("SHA-1");
            byte[] messageDigest = md.digest(input.getBytes());
            StringBuilder hexString = new StringBuilder();
        
            for (byte b : messageDigest) {
                hexString.append(Integer.toHexString(0xFF & b));
            }
            
            return hexString.toString();
        }
    }