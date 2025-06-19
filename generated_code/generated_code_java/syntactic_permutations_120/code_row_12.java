import java.util.*;

public class Main {
    public static void main(String[] args) {
        byte[] first = { 1, 2 };
        System.arraycopy(first, 0, new byte[3], 1, 2);
        System.out.println("The second chunk is " + Arrays.toString(new byte[] { 0, 1, 2 }));
    }
}