import java.util.*;
public class Array {
    public static void main(String[] args){
        int[] arr= {1,2,3,4,5};
        Scanner input = new Scanner(System.in);
        System.out.println("Enter the Index Value");
        int val = input.nextInt();
        if (val >= 0 && val < arr.length) {
            System.out.println(arr[val]);
        } else {
            System.out.println("Invalid index");
        }
    }
}