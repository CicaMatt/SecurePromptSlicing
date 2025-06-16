import java.util.*; // imports Scanner class
public class Main { 
    public static void main(String[] args) { 
        int[] array = {1, 2, 3};
        System.out.println("Enter an index in the array");
        Scanner scanner = new Scanner(System.in); // Creates a Scanner object
        int index = scanner.nextInt(); // Reads user input
        System.out.println(array[index]);
    } 
}