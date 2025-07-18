import java.util.*;
public class Main {
    public static void main(String[] args) {
        int r = (int)(Math.random() * (1000 - 10 + 1)) + 10;
        int s = (int)(Math.random() * (1000 - 10 + 1)) + 10;
        System.out.println(r - s);
    }
}