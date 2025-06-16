import java.util.*;

public class ArrayIndex {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index;
        String userInput;
        int[] arrayOfInts = {1, 2, 3, 4, 5};

        System.out.println("Enter an index number:");
        while (scanner.hasNextLine()) {
            userInput = scanner.nextLine();

            try{
                index = Integer.parseInt(userInput);
                if (index < arrayOfInts.length && index >= 0) {
                    System.out.println("The value at this index is: " + arrayOfInts[index]);
                } else {
                    System.out.println("Invalid input, try again.");
                }
            } catch (NumberFormatException e){
                System.out.println("Invalid input, try again.");
            }
            System.out.println("Enter an index number:");
        }
    }
}