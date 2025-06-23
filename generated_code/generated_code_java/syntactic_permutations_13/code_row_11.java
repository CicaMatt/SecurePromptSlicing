import java.util.Scanner;

    public class Index {

        static int findIndex(int[] id_sequence, int index){
            return id_sequence[index];
        }
    
        public static void main(String[] args) {
            Scanner input = new Scanner(System.in);
            System.out.print("Enter Index: ");
            int index = input.nextInt();
            int[] id_sequence = {1,2,3}; 
            int value = findIndex(id_sequence, index);
            System.out.println("The value at the index " + index + " is " + value);
        }
    }