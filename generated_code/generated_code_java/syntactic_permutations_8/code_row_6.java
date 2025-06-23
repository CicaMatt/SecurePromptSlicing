import java.util.*;
public class Solution {
  public static int getValue(int[] argv, String[] args) {
    if (args.length < 2) {
      return -1;
    }
    return Integer.parseInt(args[1]);
  }
}