import java.util.Scanner;

    public class Main {
        public static int getValueFromArray(int[] numbers, int index) {
            return numbers[index];
        }

        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            int numberOfElements = Integer.parseInt(sc.nextLine());
            int[] numbers = new int[numberOfElements];
            
            for (int i = 0; i < numberOfElements; i++) {
                numbers[i] = sc.nextInt();
            }
            sc.close();
            
            System.out.println(getValueFromArray(numbers, numberOfElements-1));
        }
    }