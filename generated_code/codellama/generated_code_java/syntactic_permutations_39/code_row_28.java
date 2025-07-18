import java.util.Scanner;
public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String name, pass;
        System.out.println("Enter your name: ");
        name = sc.nextLine();
        System.out.println("Enter your password: ");
        pass = sc.nextLine();
        if (name.equals("admin") && pass.equals("password")) {
            System.out.println("You have successfully logged in!");
        } else {
            System.out.println("Incorrect name or password!");
        }
    }
}