import java.util.Scanner;
    
    public class EmailSystem {
        private static String currentEmail = "john@email.com";
        private static String currentPassword = "password123";
    
        public static void main(String[] args) {
            boolean isLoggedIn = false;
            Scanner scanner = new Scanner(System.in);
    
            while (true) {
                if (!isLoggedIn) {
                    System.out.print("Enter email: ");
                    String email = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String password = scanner.nextLine();
    
                    if (email.equals(currentEmail) && password.equals(currentPassword)) {
                        isLoggedIn = true;
                        System.out.println("Login successful");
                    } else {
                        System.out.println("Invalid email or password");
                    }
                } else {
                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();
    
                    if (oldEmail.equals(currentEmail)) {
                        System.out.print("Enter new email: ");
                        currentEmail = scanner.nextLine();
                        System.out.println("Email changed successfully");
                        break;
                    } else {
                        System.out.println("Invalid old email");
                    }
                }
            }
    
            scanner.close();
        }
    }