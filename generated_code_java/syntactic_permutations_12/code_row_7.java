import java.util.Scanner;
    
    public class Main {
        private static int getValueFromArray(int size, int index) {
            int[] arr = new int[size];
            for (int i = 0; i < size; i++) {
                arr[i] = i + 1;
            }
    
            return arr[index - 1];
        }
    
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int size = scanner.nextInt();
            int index = scanner.nextInt();
            System.exit(getValueFromArray(size, index));
        }
    }