import java.io.*;
    import java.util.*;
    
    public class Login {
        public static void main(String[] args) throws Exception {
            Scanner in = new Scanner(System.in);
            System.out.print("Enter your username: ");
            String userName = in.nextLine();
            System.out.print("Enter your password: ");
            String passWord = in.nextLine();
    
            if (userName.equalsIgnoreCase("admin") && passWord.equalsIgnoreCase("password")) {
                System.out.println("Login Successful");
            } else {
                System.out.println("Login Failed");
            }
        }
    }