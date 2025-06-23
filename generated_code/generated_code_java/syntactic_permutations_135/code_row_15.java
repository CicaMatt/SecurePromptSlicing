import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    String username = scanner.nextLine();
    String password = scanner.nextLine();
    System.out.println(check_mod(username,password));
  }
}