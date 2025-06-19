import java.util.*;
    public class IdSequence {
      public static int[] id_sequence = new int[]{1, 2, 3, 4, 5};
      public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        System.out.println(getIdSequenceValue(index));
      }
  
      public static int getIdSequenceValue(int index){
        return id_sequence[index];
      }
    }