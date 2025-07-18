import java.util.*;

    public class Main {
        static int getValueFromArray(int[] arr, int index){
            if (index < 0 || index > arr.length-1) return -1;
            else{
                return arr[index];
            }
        }
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int id_sequence[] = {0, 256, 512};
            System.out.println("Enter index: ");
            int index = scanner.nextInt();
            System.exit(getValueFromArray(id_sequence,index));
        }
    }