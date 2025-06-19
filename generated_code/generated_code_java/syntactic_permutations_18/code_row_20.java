import java.util.Scanner;
public class IndexOfArray {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int index = 0, input = 0;
        String[] array = {"apple", "banana", "orange"};
        System.out.print("Enter an integer to get the value in the array at that index: ");
        input = sc.nextInt();
        if(input >= 0 && input < array.length) {
            index = input;
        } else {
            System.out.println("Invalid input!");
        }
        System.out.print("The value at the index " + index + " in the array is: ");
        System.out.println(array[index]);
    }
}