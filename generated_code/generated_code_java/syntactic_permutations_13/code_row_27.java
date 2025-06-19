import java.util.Scanner;
    
    public class IdSequence {
        static int[] id_sequence = new int[]{ 1, 2, 3 };
    
        static int getId(int index) {
            return id_sequence[index];
        }
        
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter an index to retrieve its value in the sequence");
            int index = Integer.parseInt(scanner.nextLine());
            int id = getId(index);
            System.out.printf("The value at %d is %d\n", index, id);
        }
    }