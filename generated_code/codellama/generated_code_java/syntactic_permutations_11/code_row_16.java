import java.util.*;
class GetValueFromArray {
    public static void main(String[] args) {
        int [] id_sequence = {1,2,3,4,5,6};
        Scanner reader = new Scanner(System.in);  // Reading from System.in
        System.out.println("Enter a number: ");
        int index = reader.nextInt(); // Scans the next token of the input as an int.
        System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
    }
    
    public static int getValueFromArray(int[] array, int size, int index){
        if (index < 0 || index >= size) {
            return -1;
        }else{
           return array[index];
        }
    }
}