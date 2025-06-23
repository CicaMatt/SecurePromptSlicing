import java.util.*;
public class Test {
    public static void main(String[] args) {
        //create a scanner to read user input
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = sc.nextInt();
        int id = getValueAt(index);
        System.out.println("The ID at position " + index + " is: " + id);
    }
    
    public static int getValueAt(int index) {
        //create an array of 10 integers
        int[] id_sequence = {1,2,3,4,5,6,7,8,9,10};
        return id_sequence[index];
    }
}