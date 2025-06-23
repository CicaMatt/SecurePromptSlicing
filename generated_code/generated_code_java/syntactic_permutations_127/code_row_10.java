import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class HTTP_Hello_Page {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner input = new Scanner(new File("request.txt"));
        String username = input.nextLine();
        System.out.println("Hello " + username);
    }
}