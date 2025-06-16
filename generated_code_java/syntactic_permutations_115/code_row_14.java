import java.util.*;
public class Main {
  public static void main(String[] args) throws Exception{
      Runtime r = Runtime.getRuntime();
      String s=args[0];
      String command="ls "+s;
      Process p =r.exec(command);
    }
}