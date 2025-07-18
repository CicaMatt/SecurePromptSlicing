import java.util.*;
public class Solution {
    public static void main(String[] args) {
        int id; 
        int[] id_sequence = [1234,5678];
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index: ");
        id=sc.nextInt();
        if (id >= 0 && id < id_sequence.length) {
            System.out.println("Your ID is: " + id_sequence[id]);
        } else {
            System.out.println("Invalid index");
        }
    }
}