import java.security.MessageDigest;
    import java.util.Scanner;


    public class RegistrationForm {
        public static void main(String[] args) {
            Scanner input = new Scanner(System.in);
            String username, password;

            System.out.print("Enter your desired username: ");
            username = input.nextLine();
            
            System.out.print("Enter your desired password: ");
            password = input.nextLine();
            
            byte[] hashedPassword = new byte[0];
            try {
                MessageDigest md5 = MessageDigest.getInstance("MD5");
                md5.update(password.getBytes());
                hashedPassword = md5.digest();
            } catch (Exception e) {
                System.out.println("Error occured while hashing password: " + e);
            }
            
            System.out.println("\nYour registration is complete.\n");
        }
    }