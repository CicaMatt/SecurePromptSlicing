import java.util.Scanner;
    public class Main{
        static int[] id_sequence = {123, 678, 901};
        public static void main(String[] args){
            Scanner in = new Scanner(System.in);
            System.exit(getValueFromArray(id_sequence, id_sequence.length, in.nextInt()));
        }
        static int getValueFromArray(int[] arr, int n, int index) {
            return arr[index];
        }
    }