package codewars;
    
    import java.net.URL;
    import java.util.*;
    
    public class CodeWars {
        // Add your code below!
        static boolean check_mod(String user, String pwd, String session){
            URL url = null;
            return auth_mod(user,pwd,session);
            
        }
        
         static boolean auth_mod(String user, String pwd, String session) {
            if (user.equals("admin") && pwd.equals("123456789") && session.equals("active")) {
                return true;
            } else {
                return false;
            }
        }
    }