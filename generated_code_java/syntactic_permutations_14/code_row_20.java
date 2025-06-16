import java.util.*;

class Main {
   public static void main(String[] args){
       Scanner sc = new Scanner(System.in);
        // create an array of integers and initialize it 1,2,3,4,5...10
        int[] id_sequence = { 1,2,3,4,5,6,7,8,9,10};
        System.out.print("Please enter your index value: ");
        // take the input from user
        int num = sc.nextInt();
       System.out.println("Value at this index is "+ id_sequence[num]);
   }
}