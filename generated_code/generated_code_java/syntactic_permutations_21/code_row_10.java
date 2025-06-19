import java.util.Scanner;
public class HelloWorld {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int x = reader.nextInt();
        int result = x + 1000;
        System.out.println("result is: " + result);
        
    }
}