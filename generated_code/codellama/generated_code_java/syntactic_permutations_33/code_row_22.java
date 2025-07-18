import java.util.Scanner;
public class App {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter your URL");
        String url = sc.next();
        if (url.contains("example.com")) {
            //code for redirecting user
        } else {
            System.out.println("Error: Invalid URL");
        }
    }
}