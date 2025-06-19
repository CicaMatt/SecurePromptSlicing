import java.util.Scanner;
    public class Login {
        private static Scanner scanner = new Scanner(System.in);
        private static String username;
        private static String password;
    
        public static void main(String[] args) {
            System.out.println("Welcome to the login page");
            System.out.print("Enter your username: ");
            username = scanner.nextLine();
            System.out.print("Enter your password: ");
            password = scanner.nextLine();
            if(username.equals("admin") && password.equals("admin")){
                redirectToDashboard();
            }else{
                System.out.println("Invalid username or password");
                main(null);
            }
        }
    
        public static void redirectToDashboard() {
            System.out.println("Welcome to the dashboard");
        }
    }