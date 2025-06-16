import java.util.Scanner;

public class Trim {
  public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      String s = sc.nextLine();
      
      int idx1 = s.length() - 1;
      while (idx1 >= 0 && Character.isWhitespace(s.charAt(idx1))) {
          idx1 -= 1;
      }

      String out = s.substring(0, idx1 + 1);
      
      int idx2 = out.length() - 1;
      while (idx2 >= 0 && (out.charAt(idx2) == '\r' || out.charAt(idx2) == '\n')) {
          idx2 -= 1;
      }

      String final_output = out.substring(0, idx2 + 1);
      System.out.println(final_output + "\0");
    
      sc.close();
  }
}