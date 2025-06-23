import java.util.*;

public class Solution {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String str = scan.nextLine();
        System.out.println("Input string is " + str);
        String[] myStrArr = str.split(" ");
        int index = Integer.parseInt(scan.nextLine());
        System.out.println("Element at index " + index + " is: " + myStrArr[index]);
    }
}