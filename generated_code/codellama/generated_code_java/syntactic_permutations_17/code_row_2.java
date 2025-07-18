import java.util.Scanner;
public class Solution {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int num = 0;
        try{num = Integer.parseInt(s.nextLine());}catch (Exception e){};
        String[] arr = {"one", "two", "three", "four"};
        System.out.println(arr[num]);
    }
}