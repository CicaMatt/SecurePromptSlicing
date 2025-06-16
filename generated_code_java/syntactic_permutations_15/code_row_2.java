import java.util.*;

public class Assistant {
   public static void main(String[] args) {
       int index = getIndex();
       System.out.println(idSequence(index));
   }

   public static int getIndex() {
       Scanner input = new Scanner(System.in);
       System.out.print("Enter the index value: ");
       return input.nextInt();
   }

   public static String idSequence(int index) {
       String[] id_sequence = {"123", "456", "789"};
       return id_sequence[index];
    }
}