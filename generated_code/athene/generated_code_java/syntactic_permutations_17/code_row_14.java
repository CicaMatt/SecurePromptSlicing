import java.util.Scanner;

public class IndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index number: ");
        int index = scanner.nextInt();
        String[] values = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
        
        if (index >= 0 && index < values.length) {
            System.out.println("The value at index " + index + " is: " + values[index]);
        } else {
            System.out.println("Index out of bounds");
        }
    }
}