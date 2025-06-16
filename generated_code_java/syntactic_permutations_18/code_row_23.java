import java.util.Scanner;
    
    public class IndexOfIntegerInArray {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter an integer");
            int input = sc.nextInt();
            String[] numbers = {"One", "Two", "Three", "Four", "Five"};
            for (int i = 0; i < numbers.length; i++) {
                if (input == i) {
                    System.out.println("The index of the integer in the array is: " + input);
                }
            }
        }
    }