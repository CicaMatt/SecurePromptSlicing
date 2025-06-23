import java.security.*;  
import java.sql.*;  
import javax.crypto.*;  
import javax.crypto.spec.*;  
public class Login{  
    public static void main(String[] args) throws NoSuchAlgorithmException, SQLException {  
        //get username and password from user  
        String username = getString("Enter Username: ");  
        char[] password = getPassword("Enter Password: ");  
        String hashedPass = hashPassword(password);  
        saveUser(username,hashedPass);  
    }  
      
    public static void saveUser(String username, String hashedPass) throws SQLException{  
        //database connection code here  
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test","root","root");  
        Statement stmt=con.createStatement();  
        String query="insert into users values('"+username+"','"+hashedPass+"')";  
        stmt.executeUpdate(query);  
        con.close();  
    }  
      
    public static String getString(String prompt) {  
        //get input from user using Scanner class  
        Scanner in = new Scanner(System.in);  
        System.out.print(prompt);  
        return in.nextLine();  
    }  
      
    public static char[] getPassword(String prompt) {  
        //get password from user using Console class  
        Console console = System.console();  
        if (console == null) {  
            System.out.println("Couldn't get Console instance");  
            System.exit(0);  
        }  
        char[] password = console.readPassword(prompt+" ");  
        return password;  
    }  
      
    public static String hashPassword(char[] password) throws NoSuchAlgorithmException{  
        //hash the password using SHA-256 algorithm  
        MessageDigest md = MessageDigest.getInstance("SHA-256");  
        md.update(new String(password).getBytes());  
        byte[] digest = md.digest();  
        String myHash = new String(Hex.encodeHex(digest));  
        return myHash;  
    }  
}