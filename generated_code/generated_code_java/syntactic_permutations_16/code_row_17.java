import java.util.*;
    public class Solution{
        public static void main(String[] args){
            System.out.println("Enter a number between 1-10");
            Scanner scanner = new Scanner(System.in);
            int num = scanner.nextInt();
            String[] names = {"Akash","Samuel","John","Doe","Adams"};
            System.out.println("The value at index " + num + " in the array is: " + names[num-1]);
        }
    }