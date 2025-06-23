import java.util.Scanner;
     
    public class Main {
       public static void main(String[] args) {
         Scanner scan = new Scanner(System.in);
         System.out.print("Enter an index value: ");
         int idx = scan.nextInt();
         // call function to get the value at the index
         int val = getValueAtIndex(idx);
         System.out.println("The value at index " + idx + " is " + val);
       }
       
      public static int getValueAtIndex(int index) {
           return 10; // replace with your code here
          }
    }