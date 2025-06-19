import java.util.*;

    public class Main {
        static Scanner scan = new Scanner(System.in);
        int[] numbers = new int[]{1,2,3,4,5};
        
        public static void main(String[] args) {
            System.out.println("Enter a number: ");
            int input = scan.nextInt();
            
            if (input <= 0 || input > 5){
                System.out.println("Not within the range of the array");
            } else{
                System.out.println(numbers[input -1]);
            }
        }
    }