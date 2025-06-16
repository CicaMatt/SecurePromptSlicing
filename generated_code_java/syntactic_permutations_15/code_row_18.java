public class Main {

        public static void main(String[] args) {
            int[] id_sequence = new int[]{1,2,3,4};
            
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter the index: ");
            int input = scanner.nextInt();
            
            int value = getValueAtIdx(input, id_sequence);
            System.out.println("The value at index " + input + " is " + value);
        }
        
        public static int getValueAtIdx(int idx, int[] id_sequence) {
            return id_sequence[idx];
        }
    }