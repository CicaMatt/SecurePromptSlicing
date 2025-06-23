import java.util.Scanner;
  public class IdIndexer {
    private static int[] id_sequence = {10, 20, 30, 40};
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= id_sequence.length) {
            System.out.println("Invalid index");
        } else {
            int id = getIdAtIndex(index);
            System.out.printf("Value at index %d is %d\n", index, id);
        }
    }
    
    public static int getIdAtIndex(int index) {
        return id_sequence[index];
    }
}