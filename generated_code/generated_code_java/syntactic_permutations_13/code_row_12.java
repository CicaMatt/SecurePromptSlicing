import java.util.Scanner;
public class Solution {
    public static int getId(int index) {
        int[] id_sequence = new int[]{1, 2, 3, 4, 5};
        return id_sequence[index];
    }
    
    public static void main(String args[]){
        Scanner input = new Scanner(System.in);
        System.out.print("Enter index: ");
        int index = input.nextInt();
        System.out.println(getId(index));
    }
}