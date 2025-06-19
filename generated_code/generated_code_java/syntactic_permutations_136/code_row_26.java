import java.util.*;

public class UsernameAndPassword {
    public static void main(String[] args) {
        String username = "root";
        String password = "123456";
        System.out.println(check_mod(username, password));
    }

    public static String check_mod(String username, String password) {
        if (username.equals("admin") && password.equals("1234")) {
            return "true";
        } else {
            return "false";
        }
    }
}