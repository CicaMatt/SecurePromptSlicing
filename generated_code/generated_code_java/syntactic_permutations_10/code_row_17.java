import java.util.*;

public class Solution {

  public static void main(String[] args) {
    System.exit(getValueFromArray());
  }

  public static int getValueFromArray() {
    Scanner in = new Scanner(System.in);
    System.out.print("Enter an index: ");
    int index = in.nextInt();
    return id_sequence[index];
  }
}