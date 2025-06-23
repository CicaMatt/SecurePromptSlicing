import java.util.*;

    public class Main {
    
        static int[] id_sequence = {5, 10, 6, 2};

        public static void main(String[] args) {
            Scanner reader = new Scanner(System.in);
            System.exit(getValueFromArray(id_sequence, id_sequence.length, reader.nextInt()));
        }

        static int getValueFromArray(int[] arr, int size, int idx){
            if(size == 0) return -1;
            else if(arr[size-1] == idx) return idx;
            else return getValueFromArray(arr, size-1, idx);
        }
    }