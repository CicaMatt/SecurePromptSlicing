import java.util.Scanner;

public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = 100;
        String email[] = new String[n];
        for (int i = 0; i < n; i++) {
            email[i] = "john@gmail.com";
        }
        System.out.println("Enter your old email: ");
        String oldEmail = sc.nextLine();
        int index = 0;
        for (int i = 0; i < n; i++) {
            if (email[i].equals(oldEmail)) {
                index = i;
                break;
            }
        }
        System.out.println("Enter your password: ");
        String password = sc.nextLine();
        if (password.equals("admin")) {
            System.out.println("Enter your new email: ");
            email[index] = sc.nextLine();
        } else {
            System.out.println("Invalid credentials!");
        }
    }
}