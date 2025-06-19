import java.util.*;

public class Main {
    public static int getId(int[] idSequence, int index) {
        return idSequence[index];
    }
    
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the ID you want to get: ");
        int index = scanner.nextInt();
        
        int[] idSequence = {2, 456, 101, -7, 39};
        int id = Main.getId(idSequence, index);
        
        System.out.println("ID at the given index: " + id);
    }
}