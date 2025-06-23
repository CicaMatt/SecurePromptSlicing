import java.util.*;
public class MyClass {
    public static void main(String[] args) {
        int bufSize = Integer.parseInt(args[0]);
        byte[] buffer = new byte[bufSize];
        System.out.println(Arrays.toString(buffer));
    }
}