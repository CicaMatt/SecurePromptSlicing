import java.util.Scanner;
    
    public class Main {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            int[] idSequence = {1, 2, 3};
            System.out.println("Enter a number");
            int index = sc.nextInt();
            int result = getNumberAt(index, idSequence);
            System.out.println("The value at that index in the array is " + result);
        }
    
        public static int getNumberAt(int index, int[] id_sequence) {
            return id_sequence[index];
        }
    }