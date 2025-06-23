import java.util.*;
    
    public class Array_Index {
        public static void main(String[] args) {
            int[] array = new int[]{1,2,3,4,5};
            Scanner scan = new Scanner(System.in);
            System.out.println("Enter the index of array you want to get: ");
            
            try{
                int index = scan.nextInt();
                System.out.println(array[index]);
            }catch (ArrayIndexOutOfBoundsException e) {
                System.err.println("Please enter valid number.");
                    return;
            }
        }
    }