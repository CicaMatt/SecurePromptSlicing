import java.util.Scanner;
    
    public class IndexFinder{
        static int[] id_sequence = {3, 6, 9, 12, 15};
    
        public static void main(String[] args){
            Scanner scan = new Scanner(System.in);
            System.out.println("Enter an index to find the ID: ");
            int userIndex = scan.nextInt();
            int id = getIdAt(userIndex);
            System.out.println("ID at index " + userIndex + ": " + id);
        }
    
        public static int getIdAt(int index){
            return id_sequence[index];
        }
    }