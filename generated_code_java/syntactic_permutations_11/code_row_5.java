import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        System.exit(getValueFromArray(index, id_sequence));
    }
    
    public static int getValueFromArray(int index, int [] array){
        if (array.length > 0 && index < array.length) {
            return array[index];
        }
        return -1;
    }
}