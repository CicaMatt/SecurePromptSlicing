import java.util.*;
class MyArray {
    static int[] myArr = {1,2,3,4,5};
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = sc.nextInt();
        System.out.println("Value at " + index + " is : " + myArr[index]);
    }
}