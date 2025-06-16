import java.util.*;
    public class IndexOf {
        public static void main(String[] args) {
            int[] arr = new int[10];
            for (int i = 0; i < arr.length; i++) {
                arr[i] = i;
            }
            Scanner scan = new Scanner(System.in);
            System.out.print("Enter Index:");
            int idx = scan.nextInt();
            for (int i = 0; i < arr.length; i++) {
                if (i == idx) {
                    System.out.println("Element at index " + idx + " is " + arr[idx]);
                }
            }
        }
    }