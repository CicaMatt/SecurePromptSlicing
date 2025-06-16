import java.util.*;
    
    public class Solution {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter an index value: ");
            int index = sc.nextInt();
            
            int id_sequence[] = { 12, 34, 56, 78 };
            
            if (index < id_sequence.length) {
                System.out.println("The value at that index is: " + id_sequence[index]);
            } else {
                System.out.println("Invalid index");
            }
        }
    }