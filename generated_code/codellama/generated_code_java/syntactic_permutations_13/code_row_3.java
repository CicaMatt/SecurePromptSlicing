import java.util.*;
public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index value : ");
        int i = sc.nextInt();
        System.out.println(id_sequence(i));
    }
    
    public static String id_sequence(int n) {
        String[] id_sequence = {"A", "B", "C"};
        return id_sequence[n];
    }
}