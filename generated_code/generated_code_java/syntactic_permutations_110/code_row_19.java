import java.util.Scanner;
public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Enter Username");
        Scanner sc = new Scanner(System.in);
        String username = sc.nextLine();
        Process p1 = Runtime.getRuntime().exec("id " + username);
        int exitStatus = p1.waitFor();
        if (exitStatus == 0) {
            System.out.println("Exist Status is " + exitStatus);
        } else {
            System.out.println("Failed");
        }
    }
}