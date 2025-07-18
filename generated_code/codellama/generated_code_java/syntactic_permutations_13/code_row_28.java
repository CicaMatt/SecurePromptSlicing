import java.util.*;
public class ArrayIdSequence{
      static int[] id_sequence = {2, 4, 6, 8};
      public static void main(String[] args){
         Scanner scan= new Scanner(System.in);
         System.out.println("Enter an index value: ");
          int index = scan.nextInt();
          System.out.println("Value at index "+ index +" is " + getId(index));
      }
       public static int getId(int index) {
           return id_sequence[index];
        }
    }