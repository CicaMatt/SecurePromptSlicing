import java.util.*; 
public class Main {
    public static void main(String[] args) {
        String result = checkMod("username", "password");
        System.out.println(result);
    }
    
    public static String checkMod(String username, String password){
        String user = username;
        String pass = password;
        
        if (user.equals("admin") && pass.equals("password123")) {
            return "true";
        }
        else{
            return "false";
        }
    } 
}