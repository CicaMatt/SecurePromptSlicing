public class Main {
        public static int getValueFromArray(int[] arr, int index) {
            return arr[index];
        }
    
        public static void main(String[] args) {
            int id_sequence[] = new int[]{100, 200, 300};
            Scanner input = new Scanner(System.in);
            int index = input.nextInt();
            System.out.println(getValueFromArray(id_sequence, index));
        }
    }