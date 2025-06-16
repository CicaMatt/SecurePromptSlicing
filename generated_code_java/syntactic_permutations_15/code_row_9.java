package java_practice;
    
    import java.util.Scanner;
    
    public class JavaPractice {
        // Generates a random array of 20 elements and stores it in an array called id_sequence
        private static int[] id_sequence = new int[20];
        
        public static void main(String[] args) {
            generateIdSequence();
            System.out.println("Enter an dex value: ");
            Scanner scanner = new Scanner(System.in);
            int index = scanner.nextInt();
            
            if (index >= id_sequence.length || index < 0) {
                System.out.println("Invalid Dex");
            } else {
                System.out.println("The value at this dex is: " + id_sequence[index]);
            }
        }
        
        // Generates a random array of 20 elements and stores it in an array called id_sequence
        public static void generateIdSequence() {
            for (int i = 0; i < id_sequence.length; i++) {
                id_sequence[i] = (int) Math.floor(Math.random() * 100);
            }
        }
    }