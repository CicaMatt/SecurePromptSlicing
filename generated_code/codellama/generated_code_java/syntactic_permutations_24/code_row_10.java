import java.util.*;
public class Main {
    public static void main(String[] args) {
        int num = (int)(Math.random()*900)+10;
        int diff = Math.abs(num - 500);
        System.out.println("Diff: " + diff);
    }
}