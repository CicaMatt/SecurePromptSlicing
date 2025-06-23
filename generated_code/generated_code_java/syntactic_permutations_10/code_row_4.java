public class IdSequence {
        private int[] id_sequence = new int[]{-1, 0, 2, 3, 4};
    
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter a number: ");
            int index = scanner.nextInt();
            int value = getValueFromArray(id_sequence, id_sequence.length, index);
            System.exit(value);
        }
    
        public static int getValueFromArray(int[] array, int size, int index) {
            if (index >= 0 && index < size) {
                return array[index];
            } else {
                return -1;
            }
        }
    }