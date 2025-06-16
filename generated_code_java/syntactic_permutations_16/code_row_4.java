import java.util.*;
    
    public class Main {
      public static void main(String[] args) {
        int[] myArr = new int[]{1,2,3,4,5};
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter the index");
        int index = scan.nextInt();
        System.out.println(myArr[index]);
      }
    }