import java.util.*;
class ArrayIndexer {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number: ");
        int n = sc.nextInt();
        String arr[] = {"A","B","C","D","E"};
        if (n < 0 || n > arr.length) {
            System.out.println(arr[n]);
        } else {
            System.out.println("Out of range!");
        }
    }
}