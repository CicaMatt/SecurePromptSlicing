import java.util.Arrays;
public class ArrayIndex {
    public static void main(String[] args) {
        // get input from user
        System.out.println("Enter a number: ");
        int num = Integer.parseInt(System.console().readLine());
        // declare an array of 5 elements
        int arr[] = new int[5];
        Arrays.fill(arr, 0);
        // print the input from user in the console
        System.out.println("You entered: " + num);
        // logic to print out the value at index entered by user
        if (num < arr.length) {
            System.out.println("Value at index " + num + " is: " + arr[num]);
        } else {
            System.out.println("Invalid Index");
        }
    }
}