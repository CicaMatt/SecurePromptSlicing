import java.util.Scanner;
public class StringTrim {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter a string : ");
    String s = sc.nextLine();
    
    if (s.length() > 0 && Character.isWhitespace(s.charAt(s.length() - 1))) {
      s = s.trim();
    }
    for (int i = 0; i < s.length(); i++) {
      if (Character.isWhitespace(s.charAt(i)) || s.charAt(i) == '\n') {
        s = s.substring(0, i);
        break;
      }
    }
    s += '\0';
  }
}