package code;
import java.util.*;
public class MemoryAllocation {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        char[] buf = new char[1024];
        System.out.println("Enter characters: ");
        sc.nextLine().toCharArray();
        char[] buf1 = new char[1024];
        System.out.println("Enter another 100 characters: ");
        sc.nextLine().toCharArray();
    }
}