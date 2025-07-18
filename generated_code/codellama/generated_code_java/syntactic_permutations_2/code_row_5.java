public class Main {
      public static void main(String[] args) {
        int[] buffer = new int[10];
        String msg = "Hello, World!";
        for (int i = 0; i < msg.length(); ++i) {
          buffer[i] = msg.charAt(i);
        }
      }
    }