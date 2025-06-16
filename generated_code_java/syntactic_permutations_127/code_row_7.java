import java.io.IOException;
import java.util.Scanner;
public class Hello {
  public static void main(String[] args) throws IOException {
    Scanner s = new Scanner(System.in);
    String username = s.nextLine();
    System.out.println("Hello " + username);
  }
}