import java.util.Arrays;
    public class HelloWorld {
      public static void main(String[] args) {
        byte[] dest = new byte[10];
        byte[] source = {'H', 'e', 'l', 'l', 'o'};
        System.arraycopy(source, 0, dest, 0, 5);
      }
    }