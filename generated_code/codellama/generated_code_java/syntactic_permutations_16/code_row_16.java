import java.util.*;
    
    public class Array {
        public static void main(String[] args) {
            int[] arr = {1,2,3,4,5};
            Scanner scan = new Scanner(System.in);
            System.out.print("Enter an index number: ");
            int num = scan.nextInt();
            if(num <= 0 || num > arr.length){
                System.out.println("Invalid input!");
            }else{
                System.out.println("Value at the index "+num+" is: " +arr[num-1]);
            }
        }
    }