import java.util.*;
public class Id_Index{
    public static int getIdFromSequence(int index){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a value: ");
        int userInput = sc.nextInt();
        return id_sequence[index];
    }
    
    private static final int[] id_sequence = {1, 2, 3, 4, 5};
}