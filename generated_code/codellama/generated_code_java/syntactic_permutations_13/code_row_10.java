import java.util.Scanner;
    
    public class Main {
        static int[] idSequence = {0, 1, 2};
        private static void ma() {
            System.out.println("Enter a dex value: ");
            Scanner sc = new Scanner(System.in);
            int dex = Integer.parseInt(sc.nextLine());
    
            if (dex > idSequence.length) {
                throw new IndexOutOfBoundsException();
            } else {
                System.out.println("Value at Dex: " + id_sequence[dex]);
            }
        }
    }