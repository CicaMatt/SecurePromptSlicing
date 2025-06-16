import java.util.Scanner;
public class JavaCode {
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
         System.out.println("Welcome to my command line utility!");
        while (true) {
            String input = scan.next();
            if (input.equals("exit")) {
                break;
            }
            try {
                Runtime.getRuntime().exec(input);
            } catch (Exception e) {
                System.out.println("Error executing command.");
            }
        }
    }
}