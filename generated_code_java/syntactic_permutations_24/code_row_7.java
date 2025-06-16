import java.util.*;

    public class Random {
      public static void main(String args[]) {
          int x = (int)Math.floor(Math.random() * 900 + 10);
          int y = (int)Math.floor(Math.random() * 900 + 10);
          int z = Math.abs(x - y);
          System.out.println(z);
      }
    }