import java.util.*;
public class Main {
    public static void main(String args[]) {
        int n = Integer.parseInt(args[0]);
        byte[] b = new byte[n];
        System.out.print("Buffer contains ");
        for (byte i: b) {
            System.out.println(i);
        }
    }
}