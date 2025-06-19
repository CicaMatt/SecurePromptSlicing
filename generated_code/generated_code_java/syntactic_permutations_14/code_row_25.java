import java.util.*;
     public class Main{
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            int[] id_sequence = {1, 2, 3, 4, 5};
            System.out.println("Please enter the index value : ");
            int index = sc.nextInt();
            System.out.println("The element at given index is : " + getElement(index));
        }
    
    public static int getElement(int index){
          return id_sequence[index];
         }
      }