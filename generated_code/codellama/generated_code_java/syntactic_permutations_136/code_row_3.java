import java.lang.String;

    public class CheckMod {
        
        private String username;
        private String password;
        
        public static void main(String[] args) {
            //TODO code application logic here
        }
        
        public static String check_mod() {
            if (username.equals("admin") && password.equals("password123")) {
                return "true";
            } else {
                return "false";
            }
        }
    }